/*
 * AboutIconPanel.java
 *
 * Created on May 21, 2001, 9:10 AM
 */

package geotrans.gui;


/**
 *
 * @author  amyc
 * @version 
 */
public class AboutIconPanel extends javax.swing.JPanel {

    private java.awt.Image im;

    /** Creates new form aboutIconPanel */
    public AboutIconPanel(java.lang.String filePath) {
        initComponents ();
        
        java.net.URL url = getClass().getResource(filePath);
        try
        {   
            im = createImage((java.awt.image.ImageProducer)url.getContent());
            if (im == null)
                System.out.println("null image");
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        java.awt.MediaTracker tracker = new java.awt.MediaTracker(this);
        tracker.addImage(im, 0);
        try
        {
            tracker.waitForID(0); 
        }
        catch(InterruptedException e) {}
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the FormEditor.
     */
    private void initComponents() {//GEN-BEGIN:initComponents
        setLayout(new java.awt.BorderLayout());
    }//GEN-END:initComponents

    public void paintComponent (java.awt.Graphics g) 
    {        
        super.paintComponent(g);
        g.drawImage(im, 0, 0, this);
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables

}
