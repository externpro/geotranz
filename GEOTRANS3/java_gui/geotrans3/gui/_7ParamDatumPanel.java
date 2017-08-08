// CLASSIFICATION: UNCLASSIFIED

/******************************************************************************
* Filename        : _7ParamDatumPanel.java
*
*    Copyright (C) BAE Systems National Security Solutions Inc. 2012
*                            ALL RIGHTS RESERVED
*
* MODIFICATION HISTORY:
*
* DATE      NAME        DR#          DESCRIPTION
*
* 08/13/12  S Gillis    
******************************************************************************/

package geotrans3.gui;

import geotrans3.enumerations.DatumType;
import geotrans3.enumerations.ListType;
import geotrans3.exception.CoordinateConversionException;
import geotrans3.jni.JNIDatumLibrary;
import geotrans3.jni.JNIEllipsoidLibrary;
import geotrans3.misc.FillList;
import geotrans3.misc.Info;
import geotrans3.misc.StringHandler;
import geotrans3.utility.Constants;
import geotrans3.utility.Platform;

public class _7ParamDatumPanel extends javax.swing.JPanel
{
///  private JNICoordinateConversionService jniCoordinateConversionService;
  private JNIDatumLibrary jniDatumLibrary;
  private JNIEllipsoidLibrary jniEllipsoidLibrary;

  /**
   * Creates new form _3ParamDatumPanel
   */
  public _7ParamDatumPanel(JNIDatumLibrary _jniDatumLibrary, JNIEllipsoidLibrary _jniEllipsoidLibrary)
  {
    jniDatumLibrary = _jniDatumLibrary;
    jniEllipsoidLibrary = _jniEllipsoidLibrary;
    
    initComponents();
    new FillList(jniDatumLibrary, jniEllipsoidLibrary, ellipsoidComboBox, ListType.ELLIPSOID);

    if (Platform.isUnix)
    {
      datumCodeLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      datumNameLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      ellipsoidLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      datumShiftLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      deltaXLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      deltaYLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      deltaZLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      rotationXLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      rotationYLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      rotationZLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      scaleLabel.setFont(new java.awt.Font("Dialog", 1, 10));
      ellipsoidComboBox.setFont(new java.awt.Font("Dialog", 1, 10));
    }

  }

  /** This method is called from within the constructor to
   * initialize the form.
   * WARNING: Do NOT modify this code. The content of this method is
   * always regenerated by the Form Editor.
   */
  // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
  private void initComponents()
  {
    java.awt.GridBagConstraints gridBagConstraints;

    createDatumPanel = new javax.swing.JPanel();
    datumPanel = new javax.swing.JPanel();
    datumCodeLabel = new javax.swing.JLabel();
    datumNameLabel = new javax.swing.JLabel();
    datumCodeTextField = new javax.swing.JTextField();
    datumNameTextField = new javax.swing.JTextField();
    selectEllipsoidPanel = new javax.swing.JPanel();
    ellipsoidLabel = new javax.swing.JLabel();
    ellipsoidComboBox = new javax.swing.JComboBox();
    datumShiftLabel = new javax.swing.JLabel();
    deltaPanel = new javax.swing.JPanel();
    deltaXLabel = new javax.swing.JLabel();
    deltaYLabel = new javax.swing.JLabel();
    deltaZLabel = new javax.swing.JLabel();
    deltaXTextField = new javax.swing.JTextField();
    deltaYTextField = new javax.swing.JTextField();
    deltaZTextField = new javax.swing.JTextField();
    rotationPanel = new javax.swing.JPanel();
    rotationXLabel = new javax.swing.JLabel();
    rotationYLabel = new javax.swing.JLabel();
    rotationZLabel = new javax.swing.JLabel();
    rotationXTextField = new javax.swing.JTextField();
    rotationYTextField = new javax.swing.JTextField();
    rotationZTextField = new javax.swing.JTextField();
    scalePanel = new javax.swing.JPanel();
    scaleLabel = new javax.swing.JLabel();
    scaleTextField = new javax.swing.JTextField();

    setLayout(new java.awt.GridBagLayout());

    setPreferredSize(new java.awt.Dimension(361, 204));
    createDatumPanel.setLayout(new java.awt.GridBagLayout());

    createDatumPanel.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 18, 0, 18));
    createDatumPanel.setMaximumSize(new java.awt.Dimension(390, 244));
    createDatumPanel.setMinimumSize(new java.awt.Dimension(390, 244));
    createDatumPanel.setOpaque(false);
    createDatumPanel.setPreferredSize(new java.awt.Dimension(420, 244));
    datumPanel.setLayout(new java.awt.GridBagLayout());

    datumCodeLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
    datumCodeLabel.setText("Code:");
    datumCodeLabel.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
    gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 20);
    datumPanel.add(datumCodeLabel, gridBagConstraints);

    datumNameLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
    datumNameLabel.setText("Name:");
    datumNameLabel.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
    datumPanel.add(datumNameLabel, gridBagConstraints);

    datumCodeTextField.setText("WGE");
    datumCodeTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
    datumCodeTextField.setMinimumSize(new java.awt.Dimension(179, 19));
    datumCodeTextField.setPreferredSize(new java.awt.Dimension(179, 19));
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 1;
    gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 20);
    datumPanel.add(datumCodeTextField, gridBagConstraints);

    datumNameTextField.setText("World Geodetic System  1984");
    datumNameTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
    datumNameTextField.setMinimumSize(new java.awt.Dimension(179, 19));
    datumNameTextField.setPreferredSize(new java.awt.Dimension(179, 19));
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 1;
    gridBagConstraints.gridy = 1;
    datumPanel.add(datumNameTextField, gridBagConstraints);

    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    createDatumPanel.add(datumPanel, gridBagConstraints);

    selectEllipsoidPanel.setLayout(new java.awt.GridBagLayout());

    selectEllipsoidPanel.setPreferredSize(new java.awt.Dimension(250, 47));
    ellipsoidLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
    ellipsoidLabel.setText("Ellipsoid:");
    ellipsoidLabel.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 0;
    gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
    selectEllipsoidPanel.add(ellipsoidLabel, gridBagConstraints);

    ellipsoidComboBox.setMaximumSize(new java.awt.Dimension(400, 25));
    ellipsoidComboBox.setMinimumSize(new java.awt.Dimension(126, 8));
    ellipsoidComboBox.setPreferredSize(new java.awt.Dimension(250, 22));
    ellipsoidComboBox.addActionListener(new java.awt.event.ActionListener()
    {
      public void actionPerformed(java.awt.event.ActionEvent evt)
      {
        ellipsoidComboBoxActionPerformed(evt);
      }
    });

    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 1;
    selectEllipsoidPanel.add(ellipsoidComboBox, gridBagConstraints);

    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 1;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(4, 0, 0, 0);
    createDatumPanel.add(selectEllipsoidPanel, gridBagConstraints);

    datumShiftLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
    datumShiftLabel.setText("Datum Shift to WGS84");
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 2;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(3, 0, 0, 0);
    createDatumPanel.add(datumShiftLabel, gridBagConstraints);

    deltaPanel.setLayout(new java.awt.GridBagLayout());

    deltaXLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
    deltaXLabel.setText("Delta X (m):");
    deltaXLabel.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 12);
    deltaPanel.add(deltaXLabel, gridBagConstraints);

    deltaYLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
    deltaYLabel.setText(" Delta Y (m):");
    deltaYLabel.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 12);
    deltaPanel.add(deltaYLabel, gridBagConstraints);

    deltaZLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
    deltaZLabel.setText("Delta Z (m):");
    deltaZLabel.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    deltaPanel.add(deltaZLabel, gridBagConstraints);

    deltaXTextField.setText("0");
    deltaXTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
    deltaXTextField.setMinimumSize(new java.awt.Dimension(115, 19));
    deltaXTextField.setPreferredSize(new java.awt.Dimension(115, 19));
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 1;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 12);
    deltaPanel.add(deltaXTextField, gridBagConstraints);

    deltaYTextField.setText("0");
    deltaYTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
    deltaYTextField.setMinimumSize(new java.awt.Dimension(115, 19));
    deltaYTextField.setPreferredSize(new java.awt.Dimension(115, 19));
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 1;
    gridBagConstraints.gridy = 1;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 12);
    deltaPanel.add(deltaYTextField, gridBagConstraints);

    deltaZTextField.setText("0");
    deltaZTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
    deltaZTextField.setMinimumSize(new java.awt.Dimension(115, 19));
    deltaZTextField.setPreferredSize(new java.awt.Dimension(115, 19));
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 2;
    gridBagConstraints.gridy = 1;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    deltaPanel.add(deltaZTextField, gridBagConstraints);

    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 3;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(3, 0, 0, 0);
    createDatumPanel.add(deltaPanel, gridBagConstraints);

    rotationPanel.setLayout(new java.awt.GridBagLayout());

    rotationXLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
    rotationXLabel.setText("Rotation X:");
    rotationXLabel.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 12);
    rotationPanel.add(rotationXLabel, gridBagConstraints);

    rotationYLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
    rotationYLabel.setText("Rotation Y:");
    rotationYLabel.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 12);
    rotationPanel.add(rotationYLabel, gridBagConstraints);

    rotationZLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
    rotationZLabel.setText("Rotation Z:");
    rotationZLabel.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    rotationPanel.add(rotationZLabel, gridBagConstraints);

    rotationXTextField.setText("0");
    rotationXTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
    rotationXTextField.setMinimumSize(new java.awt.Dimension(115, 19));
    rotationXTextField.setPreferredSize(new java.awt.Dimension(115, 19));
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 1;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 12);
    rotationPanel.add(rotationXTextField, gridBagConstraints);

    rotationYTextField.setText("0");
    rotationYTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
    rotationYTextField.setMinimumSize(new java.awt.Dimension(115, 19));
    rotationYTextField.setPreferredSize(new java.awt.Dimension(115, 19));
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 1;
    gridBagConstraints.gridy = 1;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 12);
    rotationPanel.add(rotationYTextField, gridBagConstraints);

    rotationZTextField.setText("0");
    rotationZTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
    rotationZTextField.setMinimumSize(new java.awt.Dimension(115, 19));
    rotationZTextField.setPreferredSize(new java.awt.Dimension(115, 19));
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 2;
    gridBagConstraints.gridy = 1;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    rotationPanel.add(rotationZTextField, gridBagConstraints);

    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 4;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(3, 0, 0, 0);
    createDatumPanel.add(rotationPanel, gridBagConstraints);

    scalePanel.setLayout(new java.awt.GridBagLayout());

    scaleLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
    scaleLabel.setText("Scale:");
    scaleLabel.setVerticalAlignment(javax.swing.SwingConstants.BOTTOM);
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
    scalePanel.add(scaleLabel, gridBagConstraints);

    scaleTextField.setText("0");
    scaleTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
    scaleTextField.setMaximumSize(new java.awt.Dimension(115, 19));
    scaleTextField.setMinimumSize(new java.awt.Dimension(115, 19));
    scaleTextField.setPreferredSize(new java.awt.Dimension(115, 19));
    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 1;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
    scalePanel.add(scaleTextField, gridBagConstraints);

    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 5;
    gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
    gridBagConstraints.insets = new java.awt.Insets(3, 0, 0, 0);
    createDatumPanel.add(scalePanel, gridBagConstraints);

    gridBagConstraints = new java.awt.GridBagConstraints();
    gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
    add(createDatumPanel, gridBagConstraints);

  }// </editor-fold>//GEN-END:initComponents

  private void ellipsoidComboBoxActionPerformed(java.awt.event.ActionEvent evt)//GEN-FIRST:event_ellipsoidComboBoxActionPerformed
  {//GEN-HEADEREND:event_ellipsoidComboBoxActionPerformed
      ellipsoidComboBox.getSelectedIndex();
  }//GEN-LAST:event_ellipsoidComboBoxActionPerformed
public boolean createDatum()
{
    StringHandler stringHandler = new StringHandler();

    double deltaX = stringHandler.stringToDouble(deltaXTextField.getText().trim(), "Invalid Delta X");
    double deltaY = stringHandler.stringToDouble(deltaYTextField.getText().trim(), "Invalid Delta Y");
    double deltaZ = stringHandler.stringToDouble(deltaZTextField.getText().trim(), "Invalid Delta Z");
    double rotationX = stringHandler.stringToDouble(rotationXTextField.getText().trim(), "Invalid X Rotation");
    double rotationY = stringHandler.stringToDouble(rotationYTextField.getText().trim(), "Invalid Y Rotation");
    double rotationZ = stringHandler.stringToDouble(rotationZTextField.getText().trim(), "Invalid Z Rotation");
    double scale = stringHandler.stringToDouble(scaleTextField.getText().trim(), "Invalid Scale");

    if(stringHandler.getError())
    {
        stringHandler.displayErrorMsg(this);
    }
    else
    {
        try
        {
          Info ellipsoidInfo = jniEllipsoidLibrary.getEllipsoidInfo(
              ellipsoidComboBox.getSelectedIndex());
          jniDatumLibrary.defineDatum(DatumType.sevenParamDatum, 
              datumCodeTextField.getText().trim(), 
              datumNameTextField.getText().trim(),
              ellipsoidInfo.getCode(),
              deltaX, deltaY, deltaZ, 
              -1.0, -1.0, -1.0,
              (-180.0 * Constants.PI_OVER_180), (180.0 * Constants.PI_OVER_180),
              (-90.0 * Constants.PI_OVER_180), (90.0 * Constants.PI_OVER_180),
              rotationX, rotationY, rotationZ, 
              scale);
          return true;
        }
        catch(CoordinateConversionException e)
        {
            stringHandler.displayErrorMsg(this, e.getMessage());
        }
    }
    
    return false;
}

  // Variables declaration - do not modify//GEN-BEGIN:variables
  private javax.swing.JPanel createDatumPanel;
  private javax.swing.JLabel datumCodeLabel;
  private javax.swing.JTextField datumCodeTextField;
  private javax.swing.JLabel datumNameLabel;
  private javax.swing.JTextField datumNameTextField;
  private javax.swing.JPanel datumPanel;
  private javax.swing.JLabel datumShiftLabel;
  private javax.swing.JPanel deltaPanel;
  private javax.swing.JLabel deltaXLabel;
  private javax.swing.JTextField deltaXTextField;
  private javax.swing.JLabel deltaYLabel;
  private javax.swing.JTextField deltaYTextField;
  private javax.swing.JLabel deltaZLabel;
  private javax.swing.JTextField deltaZTextField;
  private javax.swing.JComboBox ellipsoidComboBox;
  private javax.swing.JLabel ellipsoidLabel;
  private javax.swing.JPanel rotationPanel;
  private javax.swing.JLabel rotationXLabel;
  private javax.swing.JTextField rotationXTextField;
  private javax.swing.JLabel rotationYLabel;
  private javax.swing.JTextField rotationYTextField;
  private javax.swing.JLabel rotationZLabel;
  private javax.swing.JTextField rotationZTextField;
  private javax.swing.JLabel scaleLabel;
  private javax.swing.JPanel scalePanel;
  private javax.swing.JTextField scaleTextField;
  private javax.swing.JPanel selectEllipsoidPanel;
  // End of variables declaration//GEN-END:variables

}

// CLASSIFICATION: UNCLASSIFIED
