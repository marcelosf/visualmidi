package proj.musicxml.note;

import proj.MusicDataElement;
import proj.util.Parser;
import proj.util.XMLReader;
import org.w3c.dom.Element;

public class Note
  implements MusicDataElement
{
  
  private NoteType noteType; //grace, cue or normal note
  private String instrument;
  private Float dynamics;
  private Float endDynamics;
  private Float attack;
  private Float release;
  private Integer timeOnly;
  private Boolean pizzicato;
  
  
  public Note(Element e)
  {
    if (XMLReader.element(e, "grace") != null)
      noteType = new GraceNote(e);
    else if (XMLReader.element(e, "cue") != null)
      noteType = new CueNote(e);
    else
      noteType = new NormalNote(e);
    Element eInstrument = XMLReader.element(e, "instrument");
    if (eInstrument != null)
      instrument = XMLReader.attribute(eInstrument, "id");
    dynamics = Parser.parseFloatNull(XMLReader.attribute(e, "dynamics"));
    endDynamics = Parser.parseFloatNull(XMLReader.attribute(e, "end-dynamics"));
    attack = Parser.parseFloatNull(XMLReader.attribute(e, "attack"));
    release = Parser.parseFloatNull(XMLReader.attribute(e, "release"));
    timeOnly = Parser.parseIntegerNull(XMLReader.attribute(e, "time-only"));
    pizzicato = Parser.parseBooleanNull(XMLReader.attribute(e, "pizzicato"));
  }

  
  public Float getAttack()
  {
    return attack;
  }

  
  public Float getDynamics()
  {
    return dynamics;
  }

  
  public Float getEndDynamics()
  {
    return endDynamics;
  }

  
  public String getInstrument()
  {
    return instrument;
  }

  
  public NoteType getNoteType()
  {
    return noteType;
  }

  
  public Boolean getPizzicato()
  {
    return pizzicato;
  }

  
  public Float getRelease()
  {
    return release;
  }

  
  public Integer getTimeOnly()
  {
    return timeOnly;
  }
  

}
