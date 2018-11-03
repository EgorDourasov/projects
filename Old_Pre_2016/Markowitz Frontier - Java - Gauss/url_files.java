/**
 * @(#)url_files.java
 *
 * url_files application
 *
 * @author Egor Dourasov
 * @version 1.00 2014/2/23
 */
import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;
import java.nio.file.StandardCopyOption.*;

public class url_files {
  
  public static void main(String[] args) throws Exception {
    
    
    //Starting month minus 1   Ex: Jan = 0, Feb = 1... etc
    String start_month = "0";
    //Starting Day
    String start_day="1";
    //Starting Year
    String start_year="2009";
    //Ending Month minus 1 - same as starting month
    String end_month="11";
    //Ending Day
    String end_day="31";
    //ending 
    String end_year="2013";
    //Frequency: d = daily, w = weekly, y = yearly
    String frequency="d";
    //Amount of tickers plus 1
    int tickers_tot = 2284;
    //Proper amount of periods plus 1: For now, m=61, w=263, d=1259
    int prop_periods= 1259; 
    
    
    
    
    
    File tickers_file = new File("tickers.txt");
    
    
    String url_loc_str;
    String file_name;
    /*  Start the Timer */
    long startTime = System.currentTimeMillis();
    
    BufferedReader in_tickers = new BufferedReader(
    new FileReader(tickers_file));
    int d=0;
    int j=1;
    String inputLine;
    while ((inputLine = in_tickers.readLine()) != null){
      try{
        
        url_loc_str = "http://ichart.yahoo.com/table.csv?s=" + inputLine + "&a=" + start_month + "&b=" + start_day + "&c=" + start_year + "&d=" + end_month + "&e=" + end_day + "&f=" + end_year + "&g=" + frequency + "&ignore=.csv";
        
        file_name = inputLine +"_"+ frequency + ".csv";
        
        URL url_loc= new URL(url_loc_str);
        
        j++;
        
        /********************************************* 
        *           Method 1 - Parsing              *
        *********************************************/ 
        PrintWriter out = new PrintWriter(new FileWriter(file_name));
        BufferedReader in = new BufferedReader(
        new InputStreamReader(url_loc.openStream()));
        
        String input_Line;
        int p=0;
        while ((input_Line = in.readLine()) != null)  {
          out.println(input_Line);
          p++;
        }
        in.close();
        out.close();
        
        File this_file = new File(file_name);
        if (p < prop_periods) {
          d++;
          this_file.renameTo(new File("incomplete/" + this_file.getName()));
        } // end of if
        System.out.print(p);
        System.out.print("  ");
        System.out.println(d);
        /********************************************* 
        *           Method 2 - file copy            *
        *******************************************
        File goog_file = new File("goog2_daily.csv");
        org.apache.commons.io.FileUtils.copyURLToFile(url_loc, goog_file);
        */
        
        
        
        
        /********************************************* 
        *           Method 3 - Bit Copy             *
        *******************************************  
        InputStream in = null;
        FileOutputStream fout = null;
        
        {
          in = URI.create(url_loc_str).toURL().openStream();
          fout = new FileOutputStream(file_name);
          
          byte data[] = new byte[1024];
          int count;
          
          while ((count = in.read(data, 0, 1024)) != -1)
          {
            fout.write(data, 0, count);
            
          }
          
        }
        */
        
      }
      catch (Exception e){
        
        continue;
      }         
      
      
    }
    in_tickers.close();
    
    
    
    
    
    /* Stop the timer and output the time*/
    long endTime   = System.currentTimeMillis();
    long totalTime = (endTime - startTime)/1000;
    
    System.out.println(totalTime);
    System.out.println(j);
    
    
  }
}