/*
 * Directory.java
 *
 * Created on August 21, 2001, 12:26 PM
 */


/**
 *
 * @author  amyc
 * @version 
 */

package geotrans.utility;

public class Directory extends Object {

    String directory;
    
    /** Creates new Directory */
    public Directory(String dir) 
    {
        directory = dir;
    }
    
    public void setDirectory(String dir)
    {
        directory = dir;
    }
    
    public String getDirectory()
    {
        return directory;
    }
}
