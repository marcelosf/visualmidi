package proj.musicxml.common;

import proj.util.Parser;
import proj.util.XMLReader;

import org.w3c.dom.Element;

public class MidiInstrument
{
  
  private String id;
  private int midiChannel;
  private String midiName;
  private int midiBank;
  private int midiProgram;
  private int midiUnpitched;
  
  
  public MidiInstrument(Element e)
  {
    id = XMLReader.attribute(e, "id");
    midiChannel = Parser.parseInt(XMLReader.elementText(e, "midi-channel"));
    midiName = XMLReader.elementText(e, "midi-name");
    midiBank = Parser.parseInt(XMLReader.elementText(e, "midi-bank"));
    midiProgram = Parser.parseInt(XMLReader.elementText(e, "midi-program"));
    midiUnpitched = Parser.parseInt(XMLReader.elementText(e, "midi-unpitched"));
  }

  
  public String getId()
  {
    return id;
  }
  
  
  public int getMidiChannel()
  {
    return midiChannel;
  }


  public String getMidiName()
  {
    return midiName;
  }
  
  
  public int getMidiBank()
  {
    return midiBank;
  }

  
  public int getMidiProgram()
  {
    return midiProgram;
  }


  
  public int getMidiUnpitched()
  {
    return midiUnpitched;
  }
 
}
