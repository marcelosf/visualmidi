package proj.util;

import java.text.*;
import java.util.Date;

public class Parser
{
  
  private Parser()
  {
  }

  public static int parseInt(String value)
  {
    try
    {
      return Integer.parseInt(value);
    }
    catch (Exception ex)
    {
      return 0;
    }
  }

  public static float parseFloat(String value)
  {
    try
    {
      return Float.parseFloat(value);
    }
    catch (Exception ex)
    {
      return 0;
    }
  }
 
  public static boolean parseBoolean(String value)
  {
    try
    {
      return Boolean.parseBoolean(value);
    }
    catch (Exception ex)
    {
      return false;
    }
  }
  
  public static Integer parseIntegerNull(String value)
  {
    try
    {
      return Integer.parseInt(value);
    }
    catch (Exception ex)
    {
      return null;
    }
  }
  
 
  public static Float parseFloatNull(String value)
  {
    try
    {
      return Float.parseFloat(value);
    }
    catch (Exception ex)
    {
      return null;
    }
  }
 
  public static Boolean parseBooleanNull(String value)
  {
    try
    {
      return Boolean.parseBoolean(value);
    }
    catch (Exception ex)
    {
      return null;
    }
  }
 
  public static Date parseDate(String value, String pattern)
  {
    try
    {
      DateFormat fmt = new SimpleDateFormat(pattern);
      return fmt.parse(value);
    }
    catch (ParseException ex)
    {
      return null;
    }
  }

}
