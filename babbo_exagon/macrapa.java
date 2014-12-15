import java.util.*; 

public class BallRemoval { 
    public String canLeave(String label) { 
      char[] c = label.toCharArray(); 
      int n = label.length(); 
      boolean[][] can = new boolean[n + 1][n + 1]; 
      for (int i = 0; i <= n; i++) { 
        can[i][i] = true; 
      } 
      for (int l = 2; l <= n; l += 2) { 
        for (int i = 0; i < n; i++) { 
          int j = i + l; 
          if (j > n) { 
            break; 
          } 
          for (int k = i + 1; k < j; k++) { 
            if (can[i + 1][k] && can[k + 1][j] && ((i > 0 && c[i] == '>') || (k < n - 1 && c[k] == '<'))) { 
              can[i][j] = true; 
            } 
          } 
        } 
      }  
      String res = ""; 
      for (int i = 0; i < n; i++) { 
        if (can[0][i] && can[i + 1][n]) { 
          res += 'o'; 
        } else { 
          res += '.'; 
        } 
      } 
      return res; 
    } 
} 