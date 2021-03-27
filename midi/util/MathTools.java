package proj.util;

public class MathTools
{
  
  private MathTools()
  {
  }

  public static int lcm(int n1, int n2)
  {
    return (n1 * n2) / gcd(n1, n2);
  }

  public static int lcm(int[] n)
  {
    if (n.length == 1)
      return n[0];
    int res = lcm(n[0], n[1]);
    for (int i = 2; i < n.length; i++)
      res = lcm(res, n[i]);
    return res;
  }

  public static int gcd(int n1, int n2)
  {
    if (n2 == 0)
      return 1;
    int r = n1 % n2;
    return (r == 0) ? n2 : gcd(n2, r);
  }

  public static int gcd(int[] n)
  {
    //first find smallest number of n[]
    int min = n[0];
    for (int i = 1; i < n.length; i++)
    {
      if (n[i] < min)
        min = n[i];
    }
    //now just try it out
    for (int i = min; i > 0; i--)
    {
      boolean ok = true;
      for (int iN = 0; iN < n.length; iN++)
      {
        if ((n[iN] % i) != 0)
        {
          ok = false;
          break;
        }
      }
      if (ok)
        return i;
    }
    return 0;
  }

}
