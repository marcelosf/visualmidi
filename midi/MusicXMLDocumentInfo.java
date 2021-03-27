package proj;

import proj.musicxml.MusicXMLDocument;
import proj.musicxml.identity.*;
import proj.musicxml.score.PartList;
import proj.musicxml.score.ScorePart;

import java.util.List;

public class MusicXMLDocumentInfo
{

  //returns movement-title, if not available, work-title
  public static String getScoreTitle(MusicXMLDocument doc)
  {
    String res = getMovementTitle(doc);
    if (res.length() < 2)
      res = getWorkTitle(doc);
    return res;
  }


  //returns composer, if available
  public static String getComposer(MusicXMLDocument doc)
  {
    String creators[][] = getCreator(doc);
    if (creators == null)
      return "";
    for (int i = 0; i < creators.length; i++)
    {
      if (creators[0][i].toLowerCase().equals("composer"))
        return creators[1][i];
    }
    return "";
  }


  public static String getWorkNumber(MusicXMLDocument doc)
  {
    try
    {
      return doc.getScorePartwise().getWork().getWorkNumber();
    }
    catch (Exception ex)
    {
      return "-";
    }
  }


  public static String getWorkTitle(MusicXMLDocument doc)
  {
    try
    {
      return doc.getScorePartwise().getWork().getWorkTitle();
    }
    catch (Exception ex)
    {
      return "-";
    }
  }


  public static String getMovementNumber(MusicXMLDocument doc)
  {
    try
    {
      return doc.getScorePartwise().getMovementNumber();
    }
    catch (Exception ex)
    {
      return "-";
    }
  }


  public static String getMovementTitle(MusicXMLDocument doc)
  {
    try
    {
      return doc.getScorePartwise().getMovementTitle();
    }
    catch (Exception ex)
    {
      return "-";
    }
  }


  public static String[][] getCreator(MusicXMLDocument doc)
  {
    try
    {
      Identification identity = doc.getScorePartwise().getIdentification();
      int count = identity.getCreators().size();
      if (count < 1)
        return null;
      String[][] res = new String[2][count];
      Creator curCreator = null;
      for (int i = 0; i < count; i++)
      {
        curCreator = identity.getCreators().get(i);
        res[0][i] = curCreator.getType();
        res[1][i] = curCreator.getValue();
      }
      return res;
    }
    catch (Exception ex)
    {
      return null;
    }
  }


  public static String[] getRights(MusicXMLDocument doc)
  {
    try
    {
      Identification identity = doc.getScorePartwise().getIdentification();
      int count = identity.getRights().size();
      if (count < 1)
        return null;
      String[] res = new String[count];
      Rights curRights = null;
      for (int i = 0; i < count; i++)
      {
        curRights = identity.getRights().get(i);
        res[i] = curRights.getValue();
      }
      return res;
    }
    catch (Exception ex)
    {
      return null;
    }
  }


  public static String getEncodingDate(MusicXMLDocument doc)
  {
    try
    {
      return doc.getScorePartwise().getIdentification().getEncoding(
        ).getEncodingDate().toString();
    }
    catch (Exception ex)
    {
      return "-";
    }
  }


  public static String getEncoder(MusicXMLDocument doc)
  {
    try
    {
      return doc.getScorePartwise().getIdentification().getEncoding(
        ).getEncoders().get(0).getValue();
    }
    catch (Exception ex)
    {
      return "-";
    }
  }


  public static String getSoftware(MusicXMLDocument doc)
  {
    try
    {
      return doc.getScorePartwise().getIdentification().getEncoding(
        ).getSoftware();
    }
    catch (Exception ex)
    {
      return "-";
    }
  }


  public static String getEncodingDescription(MusicXMLDocument doc)
  {
    try
    {
      String ret = "";
      List<String> sa = doc.getScorePartwise().getIdentification(
        ).getEncoding().getEncodingDescriptions();
      for (String s : sa)
        ret += s + "\n";
      return ret;
    }
    catch (Exception ex)
    {
      return "-";
    }
  }


  public static String[] getPartNames(MusicXMLDocument doc)
  {
    try
    {
      PartList partList = doc.getScorePartwise().getPartList();
      int count = partList.getScoreParts().size();
      String[] res = new String[count];
      if (count < 1)
        return null;
      ScorePart curScorePart = null;
      for (int i = 0; i < count; i++)
      {
        curScorePart = partList.getScoreParts().get(i);
        res[i] = curScorePart.getPartName();
      }
      return res;
    }
    catch (Exception ex)
    {
      return null;
    }
  }


}
