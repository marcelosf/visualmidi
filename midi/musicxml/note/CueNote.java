package proj.musicxml.note;

import proj.util.XMLReader;
import org.w3c.dom.Element;

public class CueNote
  implements NoteType
{
  
  private Chord chord;
  private NotePitchType notePitchType;
  private Duration duration;
  
  
  public CueNote(Element e)
  {
    if (XMLReader.element(e, "chord") != null)
      chord = new Chord();
    Element ePitch = XMLReader.element(e, "pitch");
    Element eUnpitched = XMLReader.element(e, "unpitched");
    Element eRest = XMLReader.element(e, "rest");
    if (ePitch != null)
      notePitchType = new Pitch(ePitch);
    else if (eUnpitched != null)
      notePitchType = new Unpitched();
    else if (eRest != null)
      notePitchType = new Rest();
    duration = new Duration(XMLReader.element(e, "duration"));
  }

  
  public Chord getChord()
  {
    return chord;
  }

  
  public NotePitchType getNotePitchType()
  {
    return notePitchType;
  }

  
  public Duration getDuration()
  {
    return duration;
  }
  
  
  public void setDuration(Duration duration)
  {
    this.duration = duration;
  }
  

}
