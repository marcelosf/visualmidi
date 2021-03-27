package proj.musicxml.note;

import proj.util.XMLReader;
import org.w3c.dom.Element;

public class GraceNote
  implements NoteType
{
  
  private Grace grace;
  private Chord chord;
  private NotePitchType notePitchType;
  
  
  public GraceNote(Element e)
  {
    grace = new Grace(XMLReader.element(e, "grace"));
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
  }
  
  
  public Grace getGrace()
  {
    return grace;
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
    return null;
  }
  
  
  public void setDuration(Duration duration)
  {
  }
  

}
