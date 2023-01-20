/*
 * Delete.java
 *
 * Created on September 5, 2000, 10:58 AM
 */

package geotrans.gui;


import geotrans.enumerations.ListType;
import geotrans.jni.*;
import geotrans.utility.Center;
import geotrans.utility.Platform;


/**
 *
 * @author  finnc
 * @version 
 */
public class DeleteDlg extends javax.swing.JDialog {

    private int listType;
    private int index = 0;
    
    
  /** Creates new form DeleteDlg */
    public DeleteDlg(java.awt.Frame parent,boolean modal,int lType) {
        super (parent, modal);
        listType = lType;
        initComponents ();
        
        if (listType == ListType.DATUM)
        {
            setTitle("Delete Datum");
            deleteLabel.setText("Datum:");
            new FillList(comboBox, ListType.DATUM);
        }
        else
        {
            setTitle("Delete Ellipsoid");
            deleteLabel.setText("Ellipsoid:");
            new FillList(comboBox, ListType.ELLIPSOID);
        }

        pack ();
        new Center(parent, this);        
        if (Platform.isJavaV1_3)
            deleteLabel.setForeground(java.awt.Color.black);
        if (Platform.isUnix)
        {
            deleteLabel.setFont(new java.awt.Font("Dialog", 1, 10));
            comboBox.setFont(new java.awt.Font("Dialog", 1, 10));
            okButton.setFont(new java.awt.Font("Dialog", 1, 10));
            cancelButton.setFont(new java.awt.Font("Dialog", 1, 10));
        }
  }


  /** This method is called from within the constructor to
   * initialize the form.
   * WARNING: Do NOT modify this code. The content of this method is
   * always regenerated by the FormEditor.
   */
  private void initComponents() {//GEN-BEGIN:initComponents
      comboBoxPanel = new javax.swing.JPanel();
      deleteLabel = new javax.swing.JLabel();
      comboBox = new javax.swing.JComboBox();
      buttonsPanel = new javax.swing.JPanel();
      okButton = new javax.swing.JButton();
      cancelButton = new javax.swing.JButton();
      
      getContentPane().setLayout(new java.awt.GridBagLayout());
      java.awt.GridBagConstraints gridBagConstraints4;
      
      setTitle("DELETE ");
      setResizable(false);
      addWindowListener(new java.awt.event.WindowAdapter() {
          public void windowClosing(java.awt.event.WindowEvent evt) {
              closeDialog(evt);
          }
      });
      
      comboBoxPanel.setLayout(new java.awt.GridBagLayout());
      java.awt.GridBagConstraints gridBagConstraints1;
      
      deleteLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
      deleteLabel.setText("Select Datum");
      deleteLabel.setAlignmentX(1.0F);
      gridBagConstraints1 = new java.awt.GridBagConstraints();
      gridBagConstraints1.fill = java.awt.GridBagConstraints.BOTH;
      gridBagConstraints1.insets = new java.awt.Insets(15, 20, 0, 20);
      gridBagConstraints1.anchor = java.awt.GridBagConstraints.NORTHWEST;
      comboBoxPanel.add(deleteLabel, gridBagConstraints1);
      
      comboBox.setMaximumRowCount(6);
      gridBagConstraints1 = new java.awt.GridBagConstraints();
      gridBagConstraints1.gridx = 0;
      gridBagConstraints1.gridy = 1;
      gridBagConstraints1.insets = new java.awt.Insets(0, 20, 10, 20);
      gridBagConstraints1.anchor = java.awt.GridBagConstraints.WEST;
      comboBoxPanel.add(comboBox, gridBagConstraints1);
      
      gridBagConstraints4 = new java.awt.GridBagConstraints();
      getContentPane().add(comboBoxPanel, gridBagConstraints4);
      
      buttonsPanel.setLayout(new java.awt.GridBagLayout());
      java.awt.GridBagConstraints gridBagConstraints3;
      
      okButton.setMnemonic(java.awt.event.KeyEvent.VK_O);
      okButton.setText("OK");
      okButton.setBorder(new javax.swing.border.BevelBorder(javax.swing.border.BevelBorder.RAISED));
      okButton.setMaximumSize(new java.awt.Dimension(43, 22));
      okButton.setMinimumSize(new java.awt.Dimension(43, 22));
      okButton.setPreferredSize(new java.awt.Dimension(43, 22));
      okButton.addActionListener(new java.awt.event.ActionListener() {
          public void actionPerformed(java.awt.event.ActionEvent evt) {
              okActionPerformed(evt);
          }
      });
      
      gridBagConstraints3 = new java.awt.GridBagConstraints();
      gridBagConstraints3.gridx = 0;
      gridBagConstraints3.gridy = 2;
      gridBagConstraints3.ipadx = 25;
      gridBagConstraints3.insets = new java.awt.Insets(0, 0, 0, 10);
      buttonsPanel.add(okButton, gridBagConstraints3);
      
      cancelButton.setMnemonic(java.awt.event.KeyEvent.VK_C);
      cancelButton.setText("Cancel");
      cancelButton.setBorder(new javax.swing.border.BevelBorder(javax.swing.border.BevelBorder.RAISED));
      cancelButton.setMaximumSize(new java.awt.Dimension(43, 22));
      cancelButton.setMinimumSize(new java.awt.Dimension(43, 22));
      cancelButton.setPreferredSize(new java.awt.Dimension(43, 22));
      cancelButton.addActionListener(new java.awt.event.ActionListener() {
          public void actionPerformed(java.awt.event.ActionEvent evt) {
              cancelActionPerformed(evt);
          }
      });
      
      gridBagConstraints3 = new java.awt.GridBagConstraints();
      gridBagConstraints3.gridx = 2;
      gridBagConstraints3.gridy = 2;
      gridBagConstraints3.ipadx = 25;
      gridBagConstraints3.insets = new java.awt.Insets(0, 10, 0, 0);
      buttonsPanel.add(cancelButton, gridBagConstraints3);
      
      gridBagConstraints4 = new java.awt.GridBagConstraints();
      gridBagConstraints4.gridx = 0;
      gridBagConstraints4.gridy = 1;
      gridBagConstraints4.fill = java.awt.GridBagConstraints.BOTH;
      gridBagConstraints4.insets = new java.awt.Insets(5, 0, 8, 0);
      getContentPane().add(buttonsPanel, gridBagConstraints4);
      
  }//GEN-END:initComponents

  private void cancelActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cancelActionPerformed
     setVisible (false);   
     dispose ();
  }//GEN-LAST:event_cancelActionPerformed

  private void okActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_okActionPerformed
    JNIEngine jniEngine = new JNIEngine();
    JNIStrtoval jniStrtoval = new JNIStrtoval();
    index = comboBox.getSelectedIndex();
    
    try
    {
        if (listType == ListType.DATUM)
             jniEngine.JNIRemoveDatum(jniEngine.JNIGetDatumCode(index + 1));
        else
             jniEngine.JNIRemoveEllipsoid(jniEngine.JNIGetEllipsoidCode(index + 1));
        
        setVisible (false);
        dispose ();
    }
    catch(GeotransError e)
    {
        jniStrtoval.displayErrorMsg(this, e.getMessage());
    }
    catch(JNIException e)
    {
        jniStrtoval.displayErrorMsg(this, e.getMessage());
    }

  }//GEN-LAST:event_okActionPerformed

  /** Closes the dialog */
  private void closeDialog(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_closeDialog
    setVisible (false);
    dispose ();
  }//GEN-LAST:event_closeDialog

  /**
  * @param args the command line arguments
  */
  public static void main (String args[]) {
    new DeleteDlg (new javax.swing.JFrame (), true, ListType.DATUM).show ();
  }
  

  // Return index of item to be deleted
  public int getIndex()
  {
    return (int)index;
  }
  
  // Variables declaration - do not modify//GEN-BEGIN:variables
  private javax.swing.JPanel comboBoxPanel;
  private javax.swing.JLabel deleteLabel;
  private javax.swing.JComboBox comboBox;
  private javax.swing.JPanel buttonsPanel;
  private javax.swing.JButton okButton;
  private javax.swing.JButton cancelButton;
  // End of variables declaration//GEN-END:variables

}
