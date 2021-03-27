package proj.musicxml;

import proj.MusicDataElement;
import proj.musicxml.attributes.Attributes;
import proj.musicxml.note.*;
import proj.musicxml.score.*;
import proj.util.MathTools;
import java.util.ArrayList;
import org.w3c.dom.Document;

public class MusicXMLDocument
{

  public ScorePartwise scorePartwise;


  public MusicXMLDocument(Document document)
    throws Exception
  {
    scorePartwise = new ScorePartwise(document.getDocumentElement());
  }

  public int equalizeDivisions()
  {
    //collect different division values
    ArrayList<Integer> arrayDivs = new ArrayList<Integer>();

    Part firstPart = scorePartwise.getParts().get(0);
    Measure curMeasure = null;
    Part curPart = null;
    int partCount = scorePartwise.getParts().size();
    for (int iM = 0; iM < firstPart.getMeasures().size(); iM++)
    {
      for (int iP = 0; iP < partCount; iP++)
      {
        curPart = (Part) scorePartwise.getParts().get(iP);
        curMeasure = (Measure) curPart.getMeasures().get(iM);
        for (int iE = 0; iE < curMeasure.getMusicDataElements().size(); iE++)
        {
          MusicDataElement m = curMeasure.getMusicDataElements().get(iE);
          if (m instanceof Attributes) //TODO
          {
            Attributes a = (Attributes) m;
            if (a.getDivisions() != null)
            {
              arrayDivs.add(a.getDivisions());
            }
          }
        }
      }
    }

    int[] divs = new int[arrayDivs.size()];
    for (int i = 0; i < arrayDivs.size(); i++)
      divs[i] = arrayDivs.get(i);


    int newDiv = MathTools.lcm(divs);

    //walk through the musicxml file and set new
    //divisions-value and durations
    int curDivFactor = 0;
    curPart = null;
    curMeasure = null;
    partCount = scorePartwise.getParts().size();
    for (int iP = 0; iP < partCount; iP++)
    {
      curPart = (Part) scorePartwise.getParts().get(iP);
      for (int iM = 0; iM < curPart.getMeasures().size(); iM++)
      {
        curMeasure = (Measure) curPart.getMeasures().get(iM);
        for (int iE = 0; iE < curMeasure.getMusicDataElements().size(); iE++)
        {
          MusicDataElement m = curMeasure.getMusicDataElements().get(iE);
          if (m instanceof Attributes)
          {
            Attributes a = (Attributes) m;
            if (a.getDivisions() != null)
            {
              curDivFactor = newDiv / a.getDivisions();
              a.setDivisions(newDiv);
            }
          }
          else if (m instanceof Note)
          {
            Note n = (Note) m;
            if (n.getNoteType().getDuration() != null)
            {
              n.getNoteType().setDuration(new Duration(
                n.getNoteType().getDuration().getValue() * curDivFactor));
            }
          }
          else if (m instanceof Backup)
          {
            Backup b = (Backup) m;
            if (b.getDuration() != null)
            {
              b.setDuration(new Duration(b.getDuration().getValue() * curDivFactor));
            }
          }
          else if (m instanceof Forward)
          {
            Forward f = (Forward) m;
            if (f.getDuration() != null)
            {
              f.setDuration(new Duration(f.getDuration().getValue() * curDivFactor));
            }
          }
        }
      }
    }

    return newDiv;
  }

  public int[] getMeasureRealDurations()
  {
    Part firstPart = (Part) scorePartwise.getParts().get(0);

    //find out number of measures and create array
    int measureCount = firstPart.getMeasures().size();
    int[] res = new int[measureCount];

    //compute measure durations
    Measure curMeasure = null;
    Part curPart = null;
    int partCount = scorePartwise.getParts().size();
    for (int iM = 0; iM < firstPart.getMeasures().size(); iM++)
    {
      for (int iP = 0; iP < partCount; iP++)
      {
        curPart = (Part) scorePartwise.getParts().get(iP);
        curMeasure = (Measure) curPart.getMeasures().get(iM);
        int measureLength = 0;
        for (int iE = 0; iE < curMeasure.getMusicDataElements().size(); iE++)
        {
          MusicDataElement m = curMeasure.getMusicDataElements().get(iE);
          if (m instanceof Note)
          {
            //ignore grace and chord notes
            Note n = (Note) m;
            if (n.getNoteType().getDuration() != null &&
              n.getNoteType().getChord() == null)
            {
              measureLength += n.getNoteType().getDuration().getValue();
            }
          }
          else if (m instanceof Backup)
          {
            Backup b = (Backup) m;
            measureLength -= b.getDuration().getValue();
          }
          else if (m instanceof Forward)
          {
            Forward f = (Forward) m;
            measureLength += f.getDuration().getValue();
          }
        }
        if (measureLength > res[iM])
          res[iM] = measureLength;
      }
    }
    return res;
  }

  
  public ScorePartwise getScorePartwise()
  {
    return scorePartwise;
  }

}
