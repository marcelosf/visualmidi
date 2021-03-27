package proj;

import proj.musicxml.MusicXMLDocument;
import java.awt.Component;
import java.io.OutputStream;
import java.io.PrintStream;
import javax.sound.midi.*;
import javax.swing.*;

public class Player
{
  
  public static final String APP_TITLE = "Xenoage Player 0.4";
  public static final String APP_VERSION = "0.4.2007.06.21";
  
  private Sequence seq;
  private Sequencer sequencer;
  private Synthesizer synthesizer;
  private float volume = 0.7f;
  
  private Component parentComponent;
  
  private StringBuilder consoleOutput;


  public Player(Component parentComponent)
  {
    this.parentComponent = parentComponent;
    
    consoleOutput = new StringBuilder();
    PrintStream out = new PrintStream(new StringOutputStream());
    try
    {
      System.setOut(out);
      System.setErr(out);
    }
    catch (Exception ex)
    {
      //may be blocked because of security reasons
      consoleOutput.append("Could not bind console output to application.");
    }
  
    try
    {
      //create synthesizer and sequencer
      sequencer = MidiSystem.getSequencer(false);
      synthesizer = MidiSystem.getSynthesizer();
      Transmitter seqTransmitter = sequencer.getTransmitter();
      seqTransmitter.setReceiver(synthesizer.getReceiver());
      synthesizer.open();
    }
    catch (Exception e)
    {
      MsgBox("Midi not available!", JOptionPane.ERROR_MESSAGE);
    }

  }


  public void openDocument(MusicXMLDocument doc)
  {
    try
    {
      seq = MusicXMLtoMIDI.convertMusicXMLtoMIDI(doc, this);
    }
    catch (Exception ex)
    {
      MsgBox("Could not convert MusicXML document!", JOptionPane.ERROR_MESSAGE);
      ex.printStackTrace();
    }
    
    try
    {
      sequencer.open();
      sequencer.stop();
      sequencer.setSequence(seq);
      setVolume(volume);
      sequencer.start();
    }
    catch (Exception ex)
    {
      MsgBox("Midi not available!", JOptionPane.ERROR_MESSAGE);
      ex.printStackTrace();
    }
  }


  public void MsgBox(String Msg, int MsgType)
  {
    JOptionPane.showMessageDialog(parentComponent, Msg, APP_TITLE, MsgType);
  }


  public String getTime(int time)
  {
    String mins, secs;
    mins = String.valueOf(time / 60);
    secs = String.valueOf(time % 60);
    if (secs.length() < 2)
      secs = "0" + secs;
    return mins + ":" + secs;
  }
  
  
  public float getVolume()
  {
    return volume;
  }


  /**
   * Sets the volume.
   * @param volume  value between 0 (silent) and 1 (loud)
   */
  public void setVolume(float volume)
  {
    this.volume = volume;
    MidiChannel[] channels = synthesizer.getChannels();
    
    //TODO: should be 127 (some websites say this)
    //but 255 is the real max volume! test it!
    int max = 255;
    
    for (int i = 0; i < channels.length; i++)
    {
      channels[i].controlChange(7, (int) (volume * max));
    }
  }
  
  
  public void play()
  {
    if (sequencer.getMicrosecondPosition() >= sequencer.getMicrosecondLength())
      sequencer.setMicrosecondPosition(0);
    setVolume(volume);
    sequencer.start();
  }
  
  
  public void pause()
  {
    sequencer.stop();
  }
  
  
  public void stop()
  {
    sequencer.stop();
    sequencer.setMicrosecondPosition(0);
  }
  
  
  public Sequencer getSequencer()
  {
    return sequencer;
  }
  
  
  public String getConsoleOutput()
  {
    return consoleOutput.toString();
  }
  
  
  private class StringOutputStream
    extends OutputStream
  {

    @Override public void write(int b)
    {
      char c = (char) b;
      consoleOutput.append(String.valueOf(c));
    }

  } 


}
