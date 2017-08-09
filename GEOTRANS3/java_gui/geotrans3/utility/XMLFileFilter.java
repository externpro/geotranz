// CLASSIFICATION: UNCLASSIFIED

package geotrans3.utility;


// This class creates a *.dat file filter
public class XMLFileFilter extends javax.swing.filechooser.FileFilter
{
    public boolean accept(java.io.File f)
    {
        return f.getName().toLowerCase().endsWith(".xml") || f.isDirectory();
    }
    public String getDescription()
    {
        return "XML Files (*.xml)";
    }
}

// CLASSIFICATION: UNCLASSIFIED
