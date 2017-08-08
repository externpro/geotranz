// CLASSIFICATION: UNCLASSIFIED

/*
 * FormatOptionsDlg.java
 *
 * Created on August 31, 2000, 11:34 AM
 */

package geotrans3.gui;


import geotrans3.exception.CoordinateConversionException;
import geotrans3.misc.FormatOptions;
import geotrans3.misc.StringHandler;
import geotrans3.utility.Utility;
import geotrans3.utility.Platform;


/**
 *
 * @author  finnc
 * @version 
 */

public class FormatOptionsDlg extends javax.swing.JDialog 
{
    private FormatOptions options;
    private FormatOptions origOptions;
    private StringHandler stringHandler = new StringHandler();

  /** Creates new form FormatOptionsDlg */
  public FormatOptionsDlg(java.awt.Frame parent,boolean modal, FormatOptions joptions) 
  {
    super (parent, modal);
    initComponents ();
    createButtonGroups();
    options = joptions;
    origOptions = new FormatOptions(joptions);
        
    setUnitsButton(joptions.getUnits());
    setSeparatorButton(joptions.getSeparator()); 
    setSignButton(joptions.getSignHemi()); 
    setRangeButton(joptions.getRange());
    setPrecisionButton(joptions.getPrecision());   
    leadingZerosCheckBox.setSelected(joptions.getLeadingZeros());
    setFormatString(formatTextField);
    setFormatString(newFormatTextField);
    
    if (Platform.isJavaV1_3)
    {
        formatLabel.setForeground(java.awt.Color.black);
        newFormatLabel.setForeground(java.awt.Color.black);
        geodeticUnitsLabel.setForeground(java.awt.Color.black);
        geodeticSeparatorLabel.setForeground(java.awt.Color.black);
        signHemiLabel.setForeground(java.awt.Color.black);
        longRangeLabel.setForeground(java.awt.Color.black);
        leadingZerosCheckBox.setForeground(java.awt.Color.black);
    }
    pack ();
    Utility.center(parent, this);
  }

  /** This method is called from within the constructor to
   * initialize the form.
   * WARNING: Do NOT modify this code. The content of this method is
   * always regenerated by the FormEditor.
   */
    private void initComponents() {//GEN-BEGIN:initComponents
        java.awt.GridBagConstraints gridBagConstraints;

        applyFormatPanel = new javax.swing.JPanel();
        formatLabel = new javax.swing.JLabel();
        newFormatLabel = new javax.swing.JLabel();
        formatTextField = new javax.swing.JTextField();
        newFormatTextField = new javax.swing.JTextField();
        optionsTabbedPane = new javax.swing.JTabbedPane();
        numberFormatPanel = new javax.swing.JPanel();
        unitsPanel = new javax.swing.JPanel();
        geodeticUnitsLabel = new javax.swing.JLabel();
        dmsUnitsRadioButton = new javax.swing.JRadioButton();
        dmUnitsRadioButton = new javax.swing.JRadioButton();
        dUnitsRadioButton = new javax.swing.JRadioButton();
        separatorPanel = new javax.swing.JPanel();
        geodeticSeparatorLabel = new javax.swing.JLabel();
        spaceSeparatorRadioButton = new javax.swing.JRadioButton();
        slashSeparatorRadioButton = new javax.swing.JRadioButton();
        colonSeparatorRadioButton = new javax.swing.JRadioButton();
        signHemiPanel = new javax.swing.JPanel();
        signHemiLabel = new javax.swing.JLabel();
        signRadioButton = new javax.swing.JRadioButton();
        hemiRadioButton = new javax.swing.JRadioButton();
        rangePanel = new javax.swing.JPanel();
        longRangeLabel = new javax.swing.JLabel();
        _180_180RangeRadioButton = new javax.swing.JRadioButton();
        _0_360RangeRadioButton = new javax.swing.JRadioButton();
        leadingZerosCheckBox = new javax.swing.JCheckBox();
        precisionPanel = new javax.swing.JPanel();
        _100000mPrecisionRadioButton = new javax.swing.JRadioButton();
        _10000mPrecisionRadioButton = new javax.swing.JRadioButton();
        _1000mPrecisionRadioButton = new javax.swing.JRadioButton();
        _100mPrecisionRadioButton = new javax.swing.JRadioButton();
        _10mPrecisionRadioButton = new javax.swing.JRadioButton();
        _1mPrecisionRadioButton = new javax.swing.JRadioButton();
        __1mPrecisionRadioButton = new javax.swing.JRadioButton();
        __01mPrecisionRadioButton = new javax.swing.JRadioButton();
        __001mPrecisionRadioButton = new javax.swing.JRadioButton();
        buttonsPanel = new javax.swing.JPanel();
        okButton = new javax.swing.JButton();
        cancelButton = new javax.swing.JButton();
        applyButton = new javax.swing.JButton();

        setTitle("Format");
        setName("");
        setResizable(false);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                dialogWindowClosing(evt);
            }
        });

        applyFormatPanel.setLayout(new java.awt.GridLayout(2, 1, 20, 5));

        formatLabel.setFont(new java.awt.Font("Dialog", 3, 14));
        formatLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        formatLabel.setText("Current Format:");
        applyFormatPanel.add(formatLabel);

        newFormatLabel.setFont(new java.awt.Font("Dialog", 3, 14));
        newFormatLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        newFormatLabel.setText("New  Format:");
        applyFormatPanel.add(newFormatLabel);

        formatTextField.setEditable(false);
        formatTextField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        formatTextField.setText("260 30 20.0E");
        applyFormatPanel.add(formatTextField);

        newFormatTextField.setEditable(false);
        newFormatTextField.setHorizontalAlignment(javax.swing.JTextField.CENTER);
        newFormatTextField.setText("260 30 20.00");
        applyFormatPanel.add(newFormatTextField);

        getContentPane().add(applyFormatPanel, java.awt.BorderLayout.NORTH);

        optionsTabbedPane.setFont(new java.awt.Font("Dialog", 1, 10));
        numberFormatPanel.setLayout(new java.awt.GridBagLayout());

        numberFormatPanel.setBorder(new javax.swing.border.EtchedBorder());
        unitsPanel.setLayout(new java.awt.GridBagLayout());

        unitsPanel.setBorder(new javax.swing.border.EmptyBorder(new java.awt.Insets(0, 10, 0, 0)));
        unitsPanel.setMinimumSize(new java.awt.Dimension(170, 86));
        unitsPanel.setPreferredSize(new java.awt.Dimension(170, 86));
        geodeticUnitsLabel.setText("Geodetic Units");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        unitsPanel.add(geodeticUnitsLabel, gridBagConstraints);

        dmsUnitsRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        dmsUnitsRadioButton.setSelected(true);
        dmsUnitsRadioButton.setText("Degrees / Minutes / Seconds");
        dmsUnitsRadioButton.setModel(dmsUnitsRadioButton.getModel());
        dmsUnitsRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                unitsActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        unitsPanel.add(dmsUnitsRadioButton, gridBagConstraints);

        dmUnitsRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        dmUnitsRadioButton.setText("Degrees / Minutes ");
        dmUnitsRadioButton.setModel(dmUnitsRadioButton.getModel());
        dmUnitsRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                unitsActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        unitsPanel.add(dmUnitsRadioButton, gridBagConstraints);

        dUnitsRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        dUnitsRadioButton.setText("Degrees ");
        dUnitsRadioButton.setModel(dUnitsRadioButton.getModel());
        dUnitsRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                unitsActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        unitsPanel.add(dUnitsRadioButton, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(6, 0, 3, 0);
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        numberFormatPanel.add(unitsPanel, gridBagConstraints);

        separatorPanel.setLayout(new java.awt.GridBagLayout());

        separatorPanel.setBorder(new javax.swing.border.EmptyBorder(new java.awt.Insets(0, 10, 0, 0)));
        separatorPanel.setMinimumSize(new java.awt.Dimension(150, 86));
        separatorPanel.setPreferredSize(new java.awt.Dimension(125, 86));
        geodeticSeparatorLabel.setText("Geodetic Separator");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        separatorPanel.add(geodeticSeparatorLabel, gridBagConstraints);

        spaceSeparatorRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        spaceSeparatorRadioButton.setSelected(true);
        spaceSeparatorRadioButton.setText("DD MM SS");
        spaceSeparatorRadioButton.setModel(spaceSeparatorRadioButton.getModel());
        spaceSeparatorRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                separatorActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        separatorPanel.add(spaceSeparatorRadioButton, gridBagConstraints);

        slashSeparatorRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        slashSeparatorRadioButton.setText("DD/MM/SS");
        slashSeparatorRadioButton.setModel(slashSeparatorRadioButton.getModel());
        slashSeparatorRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                separatorActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        separatorPanel.add(slashSeparatorRadioButton, gridBagConstraints);

        colonSeparatorRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        colonSeparatorRadioButton.setText("DD:MM:SS");
        colonSeparatorRadioButton.setModel(colonSeparatorRadioButton.getModel());
        colonSeparatorRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                separatorActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        separatorPanel.add(colonSeparatorRadioButton, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(6, 5, 3, 6);
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHEAST;
        numberFormatPanel.add(separatorPanel, gridBagConstraints);

        signHemiPanel.setLayout(new java.awt.GridBagLayout());

        signHemiPanel.setBorder(new javax.swing.border.EmptyBorder(new java.awt.Insets(0, 10, 0, 0)));
        signHemiPanel.setMinimumSize(new java.awt.Dimension(149, 68));
        signHemiPanel.setPreferredSize(new java.awt.Dimension(119, 68));
        signHemiLabel.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        signHemiLabel.setText("Sign /  Hemisphere");
        signHemiLabel.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        signHemiPanel.add(signHemiLabel, gridBagConstraints);

        signRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        signRadioButton.setText("+ / -");
        signRadioButton.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        signRadioButton.setModel(signRadioButton.getModel());
        signRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                signHemiActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        signHemiPanel.add(signRadioButton, gridBagConstraints);

        hemiRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        hemiRadioButton.setSelected(true);
        hemiRadioButton.setText("N / S, E / W");
        hemiRadioButton.setHorizontalAlignment(javax.swing.SwingConstants.LEFT);
        hemiRadioButton.setModel(hemiRadioButton.getModel());
        hemiRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                signHemiActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.SOUTHWEST;
        signHemiPanel.add(hemiRadioButton, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 3, 0);
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        numberFormatPanel.add(signHemiPanel, gridBagConstraints);

        rangePanel.setLayout(new java.awt.GridBagLayout());

        rangePanel.setBorder(new javax.swing.border.EmptyBorder(new java.awt.Insets(0, 10, 0, 0)));
        rangePanel.setMinimumSize(new java.awt.Dimension(119, 88));
        rangePanel.setPreferredSize(new java.awt.Dimension(110, 68));
        longRangeLabel.setText("Longitude Range");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        rangePanel.add(longRangeLabel, gridBagConstraints);

        _180_180RangeRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        _180_180RangeRadioButton.setSelected(true);
        _180_180RangeRadioButton.setText("( -180, 180 )");
        _180_180RangeRadioButton.setModel(_180_180RangeRadioButton.getModel());
        _180_180RangeRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                rangeActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        rangePanel.add(_180_180RangeRadioButton, gridBagConstraints);

        _0_360RangeRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        _0_360RangeRadioButton.setText("( 0, 360 )");
        _0_360RangeRadioButton.setModel(_0_360RangeRadioButton.getModel());
        _0_360RangeRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                rangeActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.SOUTHWEST;
        rangePanel.add(_0_360RangeRadioButton, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.insets = new java.awt.Insets(0, 5, 3, 20);
        gridBagConstraints.anchor = java.awt.GridBagConstraints.SOUTHEAST;
        numberFormatPanel.add(rangePanel, gridBagConstraints);

        leadingZerosCheckBox.setText("Leading Zeros");
        leadingZerosCheckBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                leadingZerosCheckBoxActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.insets = new java.awt.Insets(0, 11, 6, 0);
        gridBagConstraints.anchor = java.awt.GridBagConstraints.SOUTHWEST;
        numberFormatPanel.add(leadingZerosCheckBox, gridBagConstraints);

        optionsTabbedPane.addTab("Number Format", null, numberFormatPanel, "");

        precisionPanel.setLayout(new java.awt.GridLayout(9, 1));

        precisionPanel.setBorder(new javax.swing.border.CompoundBorder(new javax.swing.border.EtchedBorder(), new javax.swing.border.EmptyBorder(new java.awt.Insets(0, 10, 0, 0))));
        _100000mPrecisionRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        _100000mPrecisionRadioButton.setText("100,000m  1 Degree");
        _100000mPrecisionRadioButton.setModel(_100000mPrecisionRadioButton.getModel());
        _100000mPrecisionRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                precisionActionPerformed(evt);
            }
        });

        precisionPanel.add(_100000mPrecisionRadioButton);

        _10000mPrecisionRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        _10000mPrecisionRadioButton.setText("10,000m    10 Minutes");
        _10000mPrecisionRadioButton.setModel(_10000mPrecisionRadioButton.getModel());
        _10000mPrecisionRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                precisionActionPerformed(evt);
            }
        });

        precisionPanel.add(_10000mPrecisionRadioButton);

        _1000mPrecisionRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        _1000mPrecisionRadioButton.setText("1000m       1 Minute");
        _1000mPrecisionRadioButton.setModel(_1000mPrecisionRadioButton.getModel());
        _1000mPrecisionRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                precisionActionPerformed(evt);
            }
        });

        precisionPanel.add(_1000mPrecisionRadioButton);

        _100mPrecisionRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        _100mPrecisionRadioButton.setText("100m         10 Seconds");
        _100mPrecisionRadioButton.setModel(_100mPrecisionRadioButton.getModel());
        _100mPrecisionRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                precisionActionPerformed(evt);
            }
        });

        precisionPanel.add(_100mPrecisionRadioButton);

        _10mPrecisionRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        _10mPrecisionRadioButton.setText("10m           1 Second");
        _10mPrecisionRadioButton.setModel(_10mPrecisionRadioButton.getModel());
        _10mPrecisionRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                precisionActionPerformed(evt);
            }
        });

        precisionPanel.add(_10mPrecisionRadioButton);

        _1mPrecisionRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        _1mPrecisionRadioButton.setSelected(true);
        _1mPrecisionRadioButton.setText("1m             0.1 Second");
        _1mPrecisionRadioButton.setModel(_1mPrecisionRadioButton.getModel());
        _1mPrecisionRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                precisionActionPerformed(evt);
            }
        });

        precisionPanel.add(_1mPrecisionRadioButton);

        __1mPrecisionRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        __1mPrecisionRadioButton.setText("0.1m          0.01 Second");
        __1mPrecisionRadioButton.setModel(__1mPrecisionRadioButton.getModel());
        __1mPrecisionRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                precisionActionPerformed(evt);
            }
        });

        precisionPanel.add(__1mPrecisionRadioButton);

        __01mPrecisionRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        __01mPrecisionRadioButton.setText("0.01m        0.001 Second");
        __01mPrecisionRadioButton.setModel(__01mPrecisionRadioButton.getModel());
        __01mPrecisionRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                precisionActionPerformed(evt);
            }
        });

        precisionPanel.add(__01mPrecisionRadioButton);

        __001mPrecisionRadioButton.setFont(new java.awt.Font("Dialog", 0, 10));
        __001mPrecisionRadioButton.setText("0.001m      0.0001 Second");
        __001mPrecisionRadioButton.setModel(__001mPrecisionRadioButton.getModel());
        __001mPrecisionRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                precisionActionPerformed(evt);
            }
        });

        precisionPanel.add(__001mPrecisionRadioButton);

        optionsTabbedPane.addTab("Precision", null, precisionPanel, "");

        getContentPane().add(optionsTabbedPane, java.awt.BorderLayout.CENTER);

        buttonsPanel.setLayout(new java.awt.GridBagLayout());

        buttonsPanel.setMinimumSize(new java.awt.Dimension(204, 41));
        buttonsPanel.setPreferredSize(new java.awt.Dimension(204, 41));
        okButton.setMnemonic(java.awt.event.KeyEvent.VK_O);
        okButton.setText("OK");
        okButton.setBorder(new javax.swing.border.BevelBorder(javax.swing.border.BevelBorder.RAISED));
        okButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                okActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.ipadx = 55;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 25);
        buttonsPanel.add(okButton, gridBagConstraints);

        cancelButton.setMnemonic(java.awt.event.KeyEvent.VK_C);
        cancelButton.setText("Cancel");
        cancelButton.setBorder(new javax.swing.border.BevelBorder(javax.swing.border.BevelBorder.RAISED));
        cancelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cancelActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.ipadx = 30;
        buttonsPanel.add(cancelButton, gridBagConstraints);

        applyButton.setMnemonic(java.awt.event.KeyEvent.VK_A);
        applyButton.setText("Apply");
        applyButton.setBorder(new javax.swing.border.BevelBorder(javax.swing.border.BevelBorder.RAISED));
        applyButton.setSelected(true);
        applyButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                applyActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.ipadx = 30;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.EAST;
        gridBagConstraints.insets = new java.awt.Insets(0, 25, 0, 0);
        buttonsPanel.add(applyButton, gridBagConstraints);

        getContentPane().add(buttonsPanel, java.awt.BorderLayout.SOUTH);

    }//GEN-END:initComponents

    private void leadingZerosCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_leadingZerosCheckBoxActionPerformed
      if(leadingZerosCheckBox.isSelected())
        options.setLeadingZeros(true);
      else
        options.setLeadingZeros(false);
    }//GEN-LAST:event_leadingZerosCheckBoxActionPerformed

  private void dialogWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_dialogWindowClosing
    options.reset(origOptions);
    setVisible (false);
    dispose ();
  }//GEN-LAST:event_dialogWindowClosing

  private void applyActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_applyActionPerformed
    setFormatString(newFormatTextField);
  }//GEN-LAST:event_applyActionPerformed

  private void cancelActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cancelActionPerformed
    options.reset(origOptions);
    setVisible (false);
    dispose ();
  }//GEN-LAST:event_cancelActionPerformed

  private void okActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_okActionPerformed
    setVisible (false);
    dispose();
  }//GEN-LAST:event_okActionPerformed

  private void precisionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_precisionActionPerformed
    if (_100000mPrecisionRadioButton.isSelected()) 
        options.setPrecision(FormatOptions.MET100000);
    else if (_10000mPrecisionRadioButton.isSelected()) 
        options.setPrecision(FormatOptions.MET10000);
    else if (_1000mPrecisionRadioButton.isSelected()) 
        options.setPrecision(FormatOptions.MET1000);
    else if (_100mPrecisionRadioButton.isSelected()) 
        options.setPrecision(FormatOptions.MET100);
    else if (_10mPrecisionRadioButton.isSelected()) 
        options.setPrecision(FormatOptions.MET10);
    else if (_1mPrecisionRadioButton.isSelected()) 
        options.setPrecision(FormatOptions.MET1);
    else if (__1mPrecisionRadioButton.isSelected())
    {
        stringHandler.displayWarningMsg(this, "Warning:  Output accuracy is limited to ~1m");
        options.setPrecision(FormatOptions.MET_1);
    }
    else if (__01mPrecisionRadioButton.isSelected()) 
    {
        stringHandler.displayWarningMsg(this, "Warning:  Output accuracy is limited to ~1m");
        options.setPrecision(FormatOptions.MET_01);
    }
    else if (__001mPrecisionRadioButton.isSelected()) 
    {
        stringHandler.displayWarningMsg(this, "Warning:  Output accuracy is limited to ~1m");
        options.setPrecision(FormatOptions.MET_001);
    }
  }//GEN-LAST:event_precisionActionPerformed

  private void rangeActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_rangeActionPerformed
    if (_180_180RangeRadioButton.isSelected()) 
        options.setRange(FormatOptions._180_180);
    else if (_0_360RangeRadioButton.isSelected()) 
        options.setRange(FormatOptions._0_360);
  }//GEN-LAST:event_rangeActionPerformed

  private void signHemiActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_signHemiActionPerformed
    if (signRadioButton.isSelected()) 
        options.setSignHemi(FormatOptions.SIGN);
    else if (hemiRadioButton.isSelected()) 
        options.setSignHemi(FormatOptions.HEMI);
  }//GEN-LAST:event_signHemiActionPerformed

  private void separatorActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_separatorActionPerformed
    if (spaceSeparatorRadioButton.isSelected()) 
        options.setSeparator(FormatOptions.SPACE);
    else if (slashSeparatorRadioButton.isSelected()) 
        options.setSeparator(FormatOptions.SLASH);
    else if (colonSeparatorRadioButton.isSelected()) 
        options.setSeparator(FormatOptions.COLON);
  }//GEN-LAST:event_separatorActionPerformed

  private void unitsActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_unitsActionPerformed
    if (dmsUnitsRadioButton.isSelected()) 
        options.setUnits(FormatOptions.DMS);
    else if (dmUnitsRadioButton.isSelected()) 
        options.setUnits(FormatOptions.DM);
    else if (dUnitsRadioButton.isSelected()) 
        options.setUnits(FormatOptions.DEG);
  }//GEN-LAST:event_unitsActionPerformed
     
    private void setUnitsButton(int units)
    { 
        if (units == options.DMS)
            dmsUnitsRadioButton.setSelected(true);
        else if (units == options.DM)
            dmUnitsRadioButton.setSelected(true);
        else if (units == options.DEG)
            dUnitsRadioButton.setSelected(true);
    }
    
    private void setSeparatorButton(int separator)
    {    
        if (separator == options.SPACE)
            spaceSeparatorRadioButton.setSelected(true);
        else if (separator == options.SLASH)
            slashSeparatorRadioButton.setSelected(true);
        else if (separator == options.COLON)
            colonSeparatorRadioButton.setSelected(true);
    }
    
    private void setSignButton(int signHemi)
    { 
        if (signHemi == options.SIGN)
            signRadioButton.setSelected(true);
        else if (signHemi == options.HEMI)
            hemiRadioButton.setSelected(true);
    }
    
    private void setRangeButton(int range)
    {    
        if (range == options._0_360)
            _0_360RangeRadioButton.setSelected(true);
        else if (range == options._180_180)
            _180_180RangeRadioButton.setSelected(true);
    }
    
    private void setPrecisionButton(int precis)
    {  
        if (precis == options.MET100000)
            _100000mPrecisionRadioButton.setSelected(true);
        else if (precis == options.MET10000)
            _10000mPrecisionRadioButton.setSelected(true);
        else if (precis == options.MET1000)
            _1000mPrecisionRadioButton.setSelected(true);
        else if (precis == options.MET100)
            _100mPrecisionRadioButton.setSelected(true);
        else if (precis == options.MET10)
            _10mPrecisionRadioButton.setSelected(true);
        else if (precis == options.MET1)
            _1mPrecisionRadioButton.setSelected(true);
        else if (precis == options.MET_1)
            __1mPrecisionRadioButton.setSelected(true);
        else if (precis == options.MET_01)
            __01mPrecisionRadioButton.setSelected(true);
        else if (precis == options.MET_001)
            __001mPrecisionRadioButton.setSelected(true);
    }
    
    private void setFormatString(javax.swing.JTextField textField)
    {
        try
        {
             java.lang.String new_test_Str;
             new_test_Str = stringHandler.longitudeToString(260.50555555555553, options.getUseNSEW(), options.getUseMinutes(), options.getUseSeconds());
             textField.setText(new_test_Str);
        }
        catch(CoordinateConversionException e)
        {
            stringHandler.displayErrorMsg(this, e.getMessage());
        }
    }
        
  // Create unit, separator, sign, range, precision button groups
  public void createButtonGroups()
  {
    javax.swing.ButtonGroup unit_group = new javax.swing.ButtonGroup();
    javax.swing.ButtonGroup separator_group = new javax.swing.ButtonGroup();
    javax.swing.ButtonGroup sign_group = new javax.swing.ButtonGroup();
    javax.swing.ButtonGroup range_group = new javax.swing.ButtonGroup();
    javax.swing.ButtonGroup precision_group = new javax.swing.ButtonGroup();

    unit_group.add(dmsUnitsRadioButton); 
    unit_group.add(dmUnitsRadioButton);     
    unit_group.add(dUnitsRadioButton); 
    
    separator_group.add(spaceSeparatorRadioButton);
    separator_group.add(slashSeparatorRadioButton);
    separator_group.add(colonSeparatorRadioButton);
    
    sign_group.add(signRadioButton);
    sign_group.add(hemiRadioButton);
    
    range_group.add(_180_180RangeRadioButton);
    range_group.add(_0_360RangeRadioButton);

    precision_group.add(_100000mPrecisionRadioButton); 
    precision_group.add(_10000mPrecisionRadioButton); 
    precision_group.add(_1000mPrecisionRadioButton); 
    precision_group.add(_100mPrecisionRadioButton); 
    precision_group.add(_10mPrecisionRadioButton); 
    precision_group.add(_1mPrecisionRadioButton); 
    precision_group.add(__1mPrecisionRadioButton); 
    precision_group.add(__01mPrecisionRadioButton); 
    precision_group.add(__001mPrecisionRadioButton); 
  }

  /**
   *
  * @param args the command line arguments
  */
  public static void main (String args[]) {
 /*   try
    {
      jOptions options = new jOptions(new msp.ccs.jni.JNICoordinateConversionService());
      new FormatOptionsDlg (new javax.swing.JFrame (), true, options).show ();
    }
    catch(Exception e)
    {
      System.out.println(e.getMessage());
    }*/
  }


    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JRadioButton _0_360RangeRadioButton;
    private javax.swing.JRadioButton _100000mPrecisionRadioButton;
    private javax.swing.JRadioButton _10000mPrecisionRadioButton;
    private javax.swing.JRadioButton _1000mPrecisionRadioButton;
    private javax.swing.JRadioButton _100mPrecisionRadioButton;
    private javax.swing.JRadioButton _10mPrecisionRadioButton;
    private javax.swing.JRadioButton _180_180RangeRadioButton;
    private javax.swing.JRadioButton _1mPrecisionRadioButton;
    private javax.swing.JRadioButton __001mPrecisionRadioButton;
    private javax.swing.JRadioButton __01mPrecisionRadioButton;
    private javax.swing.JRadioButton __1mPrecisionRadioButton;
    private javax.swing.JButton applyButton;
    private javax.swing.JPanel applyFormatPanel;
    private javax.swing.JPanel buttonsPanel;
    private javax.swing.JButton cancelButton;
    private javax.swing.JRadioButton colonSeparatorRadioButton;
    private javax.swing.JRadioButton dUnitsRadioButton;
    private javax.swing.JRadioButton dmUnitsRadioButton;
    private javax.swing.JRadioButton dmsUnitsRadioButton;
    private javax.swing.JLabel formatLabel;
    private javax.swing.JTextField formatTextField;
    private javax.swing.JLabel geodeticSeparatorLabel;
    private javax.swing.JLabel geodeticUnitsLabel;
    private javax.swing.JRadioButton hemiRadioButton;
    private javax.swing.JCheckBox leadingZerosCheckBox;
    private javax.swing.JLabel longRangeLabel;
    private javax.swing.JLabel newFormatLabel;
    private javax.swing.JTextField newFormatTextField;
    private javax.swing.JPanel numberFormatPanel;
    private javax.swing.JButton okButton;
    private javax.swing.JTabbedPane optionsTabbedPane;
    private javax.swing.JPanel precisionPanel;
    private javax.swing.JPanel rangePanel;
    private javax.swing.JPanel separatorPanel;
    private javax.swing.JLabel signHemiLabel;
    private javax.swing.JPanel signHemiPanel;
    private javax.swing.JRadioButton signRadioButton;
    private javax.swing.JRadioButton slashSeparatorRadioButton;
    private javax.swing.JRadioButton spaceSeparatorRadioButton;
    private javax.swing.JPanel unitsPanel;
    // End of variables declaration//GEN-END:variables

} 

// CLASSIFICATION: UNCLASSIFIED