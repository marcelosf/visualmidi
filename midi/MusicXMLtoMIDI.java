package proj;

import proj.musicxml.MusicXMLDocument;
import proj.musicxml.attributes.Attributes;
import proj.musicxml.common.MidiInstrument;
import proj.musicxml.direction.Direction;
import proj.musicxml.direction.Sound;
import proj.musicxml.note.*;
import proj.musicxml.score.*;

import javax.sound.midi.*;

public class MusicXMLtoMIDI
{

  private MusicXMLtoMIDI()
  {
  }
  //status variables:
  private static int midiVelocity = 0;

  public static Sequence convertMusicXMLtoMIDI(MusicXMLDocument doc, Player player) throws Exception
  {
    //equalize divisions-values
    int divs = doc.equalizeDivisions();
    //compute real duration of each measure
    int[] measureLengths = doc.getMeasureRealDurations();
    //create new sequence
    int tracksCount = doc.getScorePartwise().getParts().size();
    Sequence dest = new Sequence(Sequence.PPQ, divs, tracksCount);
    //fill tracks with data
    int curPos = 0;
    int lastPos = 0;
    int measureStartPos = 0;
    int measureCount = 0;
    int elementCount = 0;
    MidiEvent mE = null;
    ShortMessage mM = null;
    int curMidiChannel = 0;
    int curMidiProgram = 0;
    int curTransposeChromatic = 0;
    ScorePartwise score = doc.getScorePartwise();
    Track curTrack = null;
    ScorePart curScorePart = null;
    MidiInstrument curMidiInstrument = null;
    Part curPart = null;
    Measure curMeasure = null;
    Attributes curAttributes = null;
    Note curNote = null;
    int midiNote = 0;
    Backup curBackup = null;
    Forward curForward = null;
    Direction curDirection = null;
    Sound curSound = null;
    int timeStart = 0;
    int timeEnd = 0;
    MusicDataElement curElement = null;
    midiVelocity = 90;
    //track for tempo events (always track 0)
    Track tempoTrack = null;
    if (tracksCount > 0)
      tempoTrack = dest.getTracks()[0];
    for (int iTracks = 0; iTracks < tracksCount; iTracks++)
    {
      curTrack = dest.getTracks()[iTracks];
      curPos = 0;
      lastPos = 0;
      curTransposeChromatic = 0;
      //read part-information
      //*********************
      curScorePart = score.getPartList().getScoreParts().get(iTracks);
      //TODO: use all, not only 1st instrument
      try
      //not all files have these values set!
      {
        curMidiInstrument = curScorePart.getMidiInstruments().get(0);
        //set channel
        curMidiChannel = curMidiInstrument.getMidiChannel();
        //set program
        curMidiProgram = curMidiInstrument.getMidiProgram();
        mM = new ShortMessage();
        mM.setMessage(ShortMessage.PROGRAM_CHANGE, curMidiChannel, curMidiProgram, 0);
        mE = new MidiEvent(mM, curPos);
        curTrack.add(mE);
      }
      catch (Exception ex)
      {
      }
      //read part-data
      //**************
      curPart = score.getParts().get(iTracks);
      measureCount = curPart.getMeasures().size();
      measureStartPos = 0;
      for (int iMeasure = 0; iMeasure < measureCount; iMeasure++)
      {
        curMeasure = (Measure) curPart.getMeasures().get(iMeasure);
        //correct measure start time
        if (iMeasure > 0)
          measureStartPos += measureLengths[iMeasure - 1];
        curPos = measureStartPos;
        lastPos = curPos;
        //go through elements
        elementCount = curMeasure.getMusicDataElements().size();
        for (int iEvent = 0; iEvent < elementCount; iEvent++)
        {
          curElement = curMeasure.getMusicDataElements().get(iEvent);
          //attributes
          //**********
          if (curElement instanceof Attributes)
          {
            curAttributes = (Attributes) curElement;
            try
            {
              curTransposeChromatic = curAttributes.getTranspose().getChromatic();
            }
            catch (Exception ex)
            {
              curTransposeChromatic = 0;
            }
          }
          //note
          //****
          else if (curElement instanceof Note)
          {
            boolean goon = false; //TODO: better solution
            curNote = (Note) curElement;
            if (curNote.getNoteType() instanceof GraceNote)
              goon = false; //TODO: don't ignore grace notes
            else if (curNote.getNoteType().getChord() != null)
            {
              timeStart = lastPos;
              goon = true;
            }
            else if (curNote.getNoteType().getNotePitchType() instanceof Rest)
            {
              lastPos = curPos;
              curPos = curPos + curNote.getNoteType().getDuration().getValue();
              goon = false;
            }
            else
            {
              timeStart = curPos;
              lastPos = curPos;
              curPos = curPos + curNote.getNoteType().getDuration().getValue();
              goon = true;
            }
            if (goon)
            {
              timeEnd = timeStart
                + curNote.getNoteType().getDuration().getValue();
              midiNote = NoteToMidiNote(curNote) + curTransposeChromatic;
              //add NOTE_ON event
              mM = new ShortMessage();
              mM.setMessage(ShortMessage.NOTE_ON, curMidiChannel, midiNote,
                midiVelocity);
              mE = new MidiEvent(mM, timeStart);
              curTrack.add(mE);
              //add NOTE_OFF event
              mM = new ShortMessage();
              mM.setMessage(ShortMessage.NOTE_OFF, curMidiChannel, midiNote, 0);
              mE = new MidiEvent(mM, timeEnd);
              curTrack.add(mE);
            }
          }
          //backup
          //******
          else if (curElement instanceof Backup)
          {
            curBackup = (Backup) curElement;
            curPos = curPos - curBackup.getDuration().getValue();
            lastPos = curPos;
          }
          //forward
          //*******
          else if (curElement instanceof Forward)
          {
            curForward = (Forward) curElement;
            curPos = curPos + curForward.getDuration().getValue();
            lastPos = curPos;
          }
          //direction
          //*********
          else if (curElement instanceof Direction)
          {
            curDirection = (Direction) curElement;
            if (curDirection.getSound() != null)
            {
              curSound = curDirection.getSound();
              AddSoundEvents(curSound, curTrack, tempoTrack, curPos, player);
              curSound = null;
            }
          }
          //sound
          //*****
          else if (curElement instanceof Sound)
          {
            curSound = (Sound) curElement;
            AddSoundEvents(curSound, curTrack, tempoTrack, curPos, player);
          }

        }
      }

    }
    //javax.swing.JOptionPane.showMessageDialog(null, "went ok");
    return dest;
  }

  public static int NoteToMidiNote(Note note)
  {
    int res = 0;
    if (note.getNoteType().getNotePitchType() instanceof Pitch)
    {
      Pitch pitch = (Pitch) note.getNoteType().getNotePitchType();
      char noteStep = pitch.getStep();
      int noteAlter = 0;
      if (pitch.getAlter() != null)
        noteAlter = Math.round(pitch.getAlter()); //use only halftone steps
      int noteOctave = pitch.getOctave();
      res = (noteOctave + 1) * 12;
      //System.out.println(noteStep);
      if (noteStep == 'C')
        res += 0;
      else if (noteStep == 'D')
        res += 2;
      else if (noteStep == 'E')
        res += 4;
      else if (noteStep == 'F')
        res += 5;
      else if (noteStep == 'G')
        res += 7;
      else if (noteStep == 'A')
        res += 9;
      else if (noteStep == 'B')
        res += 11;
      res += noteAlter;
    }
    return res;
  }

  public static void AddSoundEvents(Sound sound, Track track, Track tempoTrack, int startPos, Player player)
  {
    try
    {
      MetaMessage mMetaM = null;
      MidiEvent mE = null;
      if (sound.getTempo() != null)
      {
        int midiTempo = Math.round(60000 / sound.getTempo() * 1000);
        mMetaM = new MetaMessage();
        mMetaM.setMessage(0x51, toByteArray(midiTempo), 3);
        mE = new MidiEvent(mMetaM, startPos);
        //always use the tempo track (first track) for tempo changes
        tempoTrack.add(mE);
      }
      if (sound.getDynamics() != null)
      {
        midiVelocity = Math.round(sound.getDynamics());
      }
    }
    catch (Exception e)
    {
    }
  }
  //bitshifting did not work...
  //TODO: correct this with bitshifting
  private static byte[] toByteArray(int val)
  {
    byte[] res = new byte[3];
    res[0] = (byte) (val / 0x10000);
    res[1] = (byte) ((val - res[0] * 0x10000) / 0x100);
    res[2] = (byte) (val - res[0] * 0x10000 - res[1] * 0x100);
    return res;
  }

}
