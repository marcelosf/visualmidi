package proj.musicxml.direction;

import proj.MusicDataElement;
import proj.musicxml.common.MidiInstrument;
import proj.util.Parser;
import proj.util.XMLReader;
import java.util.*;
import org.w3c.dom.Element;

public class Sound
  implements MusicDataElement
{
  
  private ArrayList<MidiInstrument> midiInstruments;
  private Float tempo;
  private Float dynamics;
  private Boolean dacapo;
  private String segno;
  private String dalsegno;
  private String coda;
  private String tocoda;
  private Integer divisions;
  private Boolean forwardRepeat;
  private String fine;
  private Integer timeOnly;
  private Boolean pizzicato;
  private Float pan;
  private Float elevation;
  private Boolean damperPedal;
  private Boolean softPedal;
  private Boolean sostenutoPedal;
  
  
  
  public Sound(Element e)
  {
    //creators
    midiInstruments = new ArrayList<MidiInstrument>();
    List<Element> eMidiInstruments = XMLReader.elements(e, "midi-instrument");
    for (Element eMidiInstrument : eMidiInstruments)
    {
      midiInstruments.add(new MidiInstrument(eMidiInstrument));
    }
    //attributes
    String attr = XMLReader.attribute(e, "tempo");
    if (attr != null)
      tempo = Parser.parseFloat(attr);
    attr = XMLReader.attribute(e, "dynamics");
    if (attr != null)
      dynamics = Parser.parseFloat(attr);
    attr = XMLReader.attribute(e, "dacapo");
    if (attr != null)
      dacapo = Parser.parseBoolean(attr);
    segno = XMLReader.attribute(e, "segno");
    dalsegno = XMLReader.attribute(e, "dalsegno");
    coda = XMLReader.attribute(e, "coda");
    tocoda = XMLReader.attribute(e, "tocoda");
    attr = XMLReader.attribute(e, "divisions");
    if (attr != null)
      divisions = Parser.parseInt(attr);
    attr = XMLReader.attribute(e, "forward-repeat");
    if (attr != null)
      forwardRepeat = Parser.parseBoolean(attr);
    fine = XMLReader.attribute(e, "fine");
    attr = XMLReader.attribute(e, "time-only");
    if (attr != null)
      timeOnly = Parser.parseInt(attr);
    attr = XMLReader.attribute(e, "pizzicato");
    if (attr != null)
      pizzicato = Parser.parseBoolean(attr);
    attr = XMLReader.attribute(e, "pan");
    if (attr != null)
      pan = Parser.parseFloat(attr);
    attr = XMLReader.attribute(e, "elevation");
    if (attr != null)
      elevation = Parser.parseFloat(attr);
    attr = XMLReader.attribute(e, "damper-pedal");
    if (attr != null)
      damperPedal = Parser.parseBoolean(attr);
    attr = XMLReader.attribute(e, "soft-pedal");
    if (attr != null)
      softPedal = Parser.parseBoolean(attr);
    attr = XMLReader.attribute(e, "sostenuto-pedal");
    if (attr != null)
      sostenutoPedal = Parser.parseBoolean(attr);
  }
  
  
  public List<MidiInstrument> getMidiInstruments()
  {
    return midiInstruments;
  }

  
  public String getCoda()
  {
    return coda;
  }

  
  public Boolean getDacapo()
  {
    return dacapo;
  }

  
  public String getDalsegno()
  {
    return dalsegno;
  }

  
  public Boolean getDamperPedal()
  {
    return damperPedal;
  }

  
  public Integer getDivisions()
  {
    return divisions;
  }

  
  public Float getDynamics()
  {
    return dynamics;
  }

  
  public Float getElevation()
  {
    return elevation;
  }

  
  public String getFine()
  {
    return fine;
  }

  
  public Boolean getForwardRepeat()
  {
    return forwardRepeat;
  }

  
  public Float getPan()
  {
    return pan;
  }

  
  public Boolean getPizzicato()
  {
    return pizzicato;
  }

  
  public String getSegno()
  {
    return segno;
  }

  
  public Boolean getSoftPedal()
  {
    return softPedal;
  }

  
  public Boolean getSostenutoPedal()
  {
    return sostenutoPedal;
  }

  
  public Float getTempo()
  {
    return tempo;
  }

  
  public Integer getTimeOnly()
  {
    return timeOnly;
  }

  
  public String getTocoda()
  {
    return tocoda;
  }

}
