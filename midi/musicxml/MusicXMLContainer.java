package proj.musicxml;

import java.io.*;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.jar.*;


public class MusicXMLContainer
{
  
  //private static final String containerPath = "META-INF/container.xml";
  
  private URL jarURL = null;
  private File jarFile = null;
  private ArrayList<String> files = new ArrayList<String>();
  
  public MusicXMLContainer(File file)
    throws Exception
  {
    this(new FileInputStream(file));
    this.jarFile = file;
  }
  

  public MusicXMLContainer(URL url)
    throws Exception
  {
    this(url.openStream());
    this.jarURL = url;
  }

  private MusicXMLContainer(InputStream in)
    throws Exception
  {
    //open the JAR input stream
	  /*
    JarInputStream jarIS = null;
    try
    {
      jarIS = new JarInputStream(in);
    }
    catch (IOException ex)
    {
      throw new Exception("Invalid MusicXML container (" + ex.toString() + ")");
    }
    //look for "META-INF/container.xml"
    
    JarEntry entry = null, container = null;
    while ((entry = jarIS.getNextJarEntry()) != null)
    {
      if (entry.getName().equals(containerPath))
      {
        container = entry;
        break;
      }
    }
    */
    /*if (container == null)
      throw new Exception("Container information is missing!");
    //read the file names from the container document
    Document doc = XMLReader.readFile(jarIS);
    Element root = XMLReader.root(doc);
    Element eRootfiles = XMLReader.element(root, "rootfiles");
    if (eRootfiles == null)
      throw new Exception("Element \"rootfiles\" is missing!");
    List<Element> eFiles = XMLReader.elements(eRootfiles, "rootfile");
    for (Element e : eFiles)
    {
      String filename = XMLReader.attribute(e, "full-path");
      if (filename != null)
        files.add(filename);
    }*/
  }

  
  public List<String> getFiles()
  {
    return files;
  }
  

  public InputStream readFile(String filename)
    throws IOException
  {
    //create input stream
    InputStream in = null;
    if (jarFile != null)
      in = new FileInputStream(jarFile);
    else
      in = jarURL.openStream();
    JarInputStream jarIS = null;
    try
    {
      jarIS = new JarInputStream(in);
    }
    catch (IOException ex)
    {
      throw new IOException("Invalid MusicXML container (" + ex.toString() + ")");
    }
    //read from input stream
    JarEntry entry;
    while ((entry = jarIS.getNextJarEntry()) != null)
    {
      if (entry.getName().equals(filename))
      {
        return jarIS;
      }
    }
    throw new IOException("Jar entry \"" + filename + "\" not found!");
  }
  

}
