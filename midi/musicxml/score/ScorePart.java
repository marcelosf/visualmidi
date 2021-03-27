package proj.musicxml.score;

import proj.musicxml.common.MidiInstrument;
import proj.musicxml.identity.Identification;
import proj.util.XMLReader;
import java.util.ArrayList;
import java.util.List;
import org.w3c.dom.Element;

public class ScorePart
{
  
  private Identification identification;
  private String partName;
  private String partAbbreviation;
  private MidiDevice midiDevice;
  private ArrayList<MidiInstrument> midiInstruments;
  
  
  public ScorePart(Element e)
  {
    Element eIdentification = XMLReader.element(e, "identification");
    if (eIdentification != null)
      identification = new Identification(eIdentification);
    partName = XMLReader.elementText(e, "part-name");
    partAbbreviation = XMLReader.elementText(e, "part-abbreviation");
    Element eMidiDevice = XMLReader.element(e, "midi-device");
    if (eMidiDevice != null)
      midiDevice = new MidiDevice(eMidiDevice);
    midiInstruments = new ArrayList<MidiInstrument>();
    List<Element> eMidiInstruments = XMLReader.elements(e, "midi-instrument");
    for (Element eMidiInstrument : eMidiInstruments)
    {
      midiInstruments.add(new MidiInstrument(eMidiInstrument));
    }
  }

  
  public Identification getIdentification()
  {
    return identification;
  }
  
  
  public String getPartName()
  {
    return partName;
  }
  
  
  public String getPartAbbreviation()
  {
    return partAbbreviation;
  }

  
  public MidiDevice getMidiDevice()
  {
    return midiDevice;
  }

  
  public List<MidiInstrument> getMidiInstruments()
  {
    return midiInstruments;
  }

}
