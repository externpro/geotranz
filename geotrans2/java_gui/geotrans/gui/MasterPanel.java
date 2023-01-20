/*
 * FilePanel.java
 *
 * Created on April 2, 2001, 3:53 PM
 */

/**
 *
 * @author  amyc
 * @version
 */

package geotrans.gui;


import geotrans.enumerations.ConversionState;
import geotrans.enumerations.CoordinateTypes;
import geotrans.enumerations.HeightType;
import geotrans.enumerations.ListType;
import geotrans.enumerations.SourceOrTarget;
import geotrans.jni.*;
import geotrans.parameters.*;
import geotrans.projections.*;
import geotrans.utility.Platform;


public class MasterPanel extends javax.swing.JPanel 
{
  private FillList datumList;
  private Geotrans parent;
  private JNIEngine jniEngine = new JNIEngine();
  private JNIStrtoval jniStrtoval = new JNIStrtoval();
  private int projectionType = CoordinateTypes.GEODETIC;
  private int datumIndex = 0;
  private int direction;
  private int state;
  private CoordPanel coordPanel;
  private int heightType;
  private long override;
  private jOptions formatOptions;
  private boolean createHeader;
  private boolean useNSEW;
  private boolean useMinutes;
  private boolean useSeconds;
  private String currLookAndFeel = "Java";
  private double _180OverPI = 180.0 / jniStrtoval.PI;

    /** Creates new form FilePanel */
    public MasterPanel(int stat, int dir, jOptions options) 
    {
        if (stat == ConversionState.CREATE_HEADER)
        {
            createHeader = true;
            state = ConversionState.FILE;    // Set state to file for engine calls
        }
        else
        {
            createHeader = false;
            state = stat;
        }
        direction = dir;
        formatOptions = options;
        if (state == ConversionState.FILE)
            init();
        else
        {
            coordPanel = new CoordPanel(options, jniStrtoval);
            init();
            java.awt.GridBagConstraints gridBagConstraints7 = new java.awt.GridBagConstraints();
            gridBagConstraints7.gridx = 0;
            gridBagConstraints7.gridy = 4;
            coordPanel.setPreferredSize(new java.awt.Dimension(469, 78));
            coordPanel.setMinimumSize(new java.awt.Dimension(469, 78));
            add( coordPanel, gridBagConstraints7 );
        }
    }

    private void init()
    {
        initComponents();

        setFormat();
        if ((direction == SourceOrTarget.SOURCE) && (state == ConversionState.FILE))
            initFileInputPanel();
        else
            initMasterPanel();

        if (Platform.isJavaV1_3)
        {
            datumLabel.setForeground(java.awt.Color.black);
            ellipsoidLabel.setForeground(java.awt.Color.black);
            inputProjectionLabel.setForeground(java.awt.Color.black);
            centralMeridianNeysParamsLabel.setForeground(java.awt.Color.black);
            originLatitudeNeysParamsLabel.setForeground(java.awt.Color.black);
            stdParallel2NeysParamsLabel.setForeground(java.awt.Color.black);
            heightLabel.setForeground(java.awt.Color.black);
            hemiBoxPanel.setForeground(java.awt.Color.black);
            _3ParamFieldsRow1LabelA.setForeground(java.awt.Color.black);
            _3ParamFieldsRow1LabelB.setForeground(java.awt.Color.black);
            _3ParamFieldsRow1LabelC.setForeground(java.awt.Color.black);
            _3ParamFieldsRow2LabelA.setForeground(java.awt.Color.black);
            _3ParamFieldsRow2LabelB.setForeground(java.awt.Color.black);
            _3ParamFieldsRow2LabelC.setForeground(java.awt.Color.black);
            _4ParamFieldsRow1LabelA.setForeground(java.awt.Color.black);
            _4ParamFieldsRow1LabelB.setForeground(java.awt.Color.black);
            _4ParamFieldsRow1LabelC.setForeground(java.awt.Color.black);
            _4ParamFieldsRow1LabelD.setForeground(java.awt.Color.black);
            _4ParamFieldsRow2LabelA.setForeground(java.awt.Color.black);
            _4ParamFieldsRow2LabelB.setForeground(java.awt.Color.black);
            _4ParamFieldsRow2LabelC.setForeground(java.awt.Color.black);
            _4ParamFieldsRow2LabelD.setForeground(java.awt.Color.black);
            zoneLabel.setForeground(java.awt.Color.black);
            zoneRangeLabel.setForeground(java.awt.Color.black);
        }
        if (Platform.isUnix)
        {
            datumLabel.setFont(new java.awt.Font("Dialog", 1, 10));
            ellipsoidLabel.setFont(new java.awt.Font("Dialog", 1, 10));
            inputProjectionLabel.setFont(new java.awt.Font("Dialog", 1, 10));
            centralMeridianNeysParamsLabel.setFont(new java.awt.Font("Dialog", 1, 10));
            originLatitudeNeysParamsLabel.setFont(new java.awt.Font("Dialog", 1, 10));
            stdParallel2NeysParamsLabel.setFont(new java.awt.Font("Dialog", 1, 10));
            heightLabel.setFont(new java.awt.Font("Dialog", 1, 10));
            hemiBoxPanel.setFont(new java.awt.Font("Dialog", 1, 10));
            _3ParamFieldsRow1LabelA.setFont(new java.awt.Font("Dialog", 1, 10));
            _3ParamFieldsRow1LabelB.setFont(new java.awt.Font("Dialog", 1, 10));
            _3ParamFieldsRow1LabelC.setFont(new java.awt.Font("Dialog", 1, 10));
            _3ParamFieldsRow2LabelA.setFont(new java.awt.Font("Dialog", 1, 10));
            _3ParamFieldsRow2LabelB.setFont(new java.awt.Font("Dialog", 1, 10));
            _3ParamFieldsRow2LabelC.setFont(new java.awt.Font("Dialog", 1, 10));
            _4ParamFieldsRow1LabelA.setFont(new java.awt.Font("Dialog", 1, 10));
            _4ParamFieldsRow1LabelB.setFont(new java.awt.Font("Dialog", 1, 10));
            _4ParamFieldsRow1LabelC.setFont(new java.awt.Font("Dialog", 1, 10));
            _4ParamFieldsRow1LabelD.setFont(new java.awt.Font("Dialog", 1, 10));
            _4ParamFieldsRow2LabelA.setFont(new java.awt.Font("Dialog", 1, 10));
            _4ParamFieldsRow2LabelB.setFont(new java.awt.Font("Dialog", 1, 10));
            _4ParamFieldsRow2LabelC.setFont(new java.awt.Font("Dialog", 1, 10));
            _4ParamFieldsRow2LabelD.setFont(new java.awt.Font("Dialog", 1, 10));
            zoneLabel.setFont(new java.awt.Font("Dialog", 1, 10));
            zoneRangeLabel.setFont(new java.awt.Font("Dialog", 1, 10));
            zoneRadioButton.setFont(new java.awt.Font("Dialog", 1, 10));
            nHemiRadioButton.setFont(new java.awt.Font("Dialog", 1, 10));
            sHemiRadioButton.setFont(new java.awt.Font("Dialog", 1, 10));
            neys71RadioButton.setFont(new java.awt.Font("Dialog", 1, 10));
            neys74RadioButton.setFont(new java.awt.Font("Dialog", 1, 10));
            datumComboBox.setFont(new java.awt.Font("Dialog", 1, 10));
            projectionComboBox.setFont(new java.awt.Font("Dialog", 1, 10));
            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                   javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 10), java.awt.Color.black));
            stdParallel1NeysParamsPanel.setBorder(new javax.swing.border.TitledBorder(null, "Std. Parallel 1:", javax.swing.border.TitledBorder.CENTER,
                                                  javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 10), java.awt.Color.black));
        }
    }


    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the FormEditor.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        java.awt.GridBagConstraints gridBagConstraints;

        datumPanel = new javax.swing.JPanel();
        datumLabel = new javax.swing.JLabel();
        ellipsoidLabel = new javax.swing.JLabel();
        datumSelectLayeredPane = new javax.swing.JLayeredPane();
        datumTextField = new javax.swing.JTextField();
        datumComboBox = new javax.swing.JComboBox();
        ellipsoidTextField = new javax.swing.JTextField();
        projectionPanel = new javax.swing.JPanel();
        inputProjectionLabel = new javax.swing.JLabel();
        projectionComboBox = new javax.swing.JComboBox();
        paramFieldsRow1LayeredPane = new javax.swing.JLayeredPane();
        _3ParamFieldsRow1Panel = new javax.swing.JPanel();
        _3ParamFieldsRow1LabelA = new javax.swing.JLabel();
        _3ParamFieldsRow1LabelB = new javax.swing.JLabel();
        _3ParamFieldsRow1LabelC = new javax.swing.JLabel();
        _3ParamFieldsRow1TextFieldA = new javax.swing.JTextField();
        _3ParamFieldsRow1TextFieldB = new javax.swing.JTextField();
        _3ParamFieldsRow1TextFieldC = new javax.swing.JTextField();
        _4ParamFieldsRow1Panel = new javax.swing.JPanel();
        _4ParamFieldsRow1LabelA = new javax.swing.JLabel();
        _4ParamFieldsRow1LabelB = new javax.swing.JLabel();
        _4ParamFieldsRow1LabelC = new javax.swing.JLabel();
        _4ParamFieldsRow1LabelD = new javax.swing.JLabel();
        _4ParamFieldsRow1TextFieldA = new javax.swing.JTextField();
        _4ParamFieldsRow1TextFieldB = new javax.swing.JTextField();
        _4ParamFieldsRow1TextFieldC = new javax.swing.JTextField();
        _4ParamFieldsRow1TextFieldD = new javax.swing.JTextField();
        neysParamsRow1Panel = new javax.swing.JPanel();
        centralMeridianNeysParamsPanel = new javax.swing.JPanel();
        centralMeridianNeysParamsLabel = new javax.swing.JLabel();
        centralMeridianNeysParamsTextField = new javax.swing.JTextField();
        originLatitudeNeysParamsPanel = new javax.swing.JPanel();
        originLatitudeNeysParamsLabel = new javax.swing.JLabel();
        originLatitudeNeysParamsTextField = new javax.swing.JTextField();
        stdParallel1NeysParamsPanel = new javax.swing.JPanel();
        neys71RadioButton = new javax.swing.JRadioButton();
        neys74RadioButton = new javax.swing.JRadioButton();
        stdParallel2NeysParamsPanel = new javax.swing.JPanel();
        stdParallel2NeysParamsLabel = new javax.swing.JLabel();
        stdParallel2NeysParamsTextField = new javax.swing.JTextField();
        heightLabelPanel = new javax.swing.JPanel();
        heightLabel = new javax.swing.JLabel();
        heightPanel = new javax.swing.JPanel();
        heightComboBox = new javax.swing.JComboBox();
        paramFieldsRow2LayeredPane = new javax.swing.JLayeredPane();
        _3ParamFieldsRow2Panel = new javax.swing.JPanel();
        _3ParamFieldsRow2LabelA = new javax.swing.JLabel();
        _3ParamFieldsRow2LabelB = new javax.swing.JLabel();
        _3ParamFieldsRow2LabelC = new javax.swing.JLabel();
        _3ParamFieldsRow2TextFieldA = new javax.swing.JTextField();
        _3ParamFieldsRow2TextFieldB = new javax.swing.JTextField();
        _3ParamFieldsRow2TextFieldC = new javax.swing.JTextField();
        _4ParamFieldsRow2Panel = new javax.swing.JPanel();
        _4ParamFieldsRow2LabelA = new javax.swing.JLabel();
        _4ParamFieldsRow2LabelB = new javax.swing.JLabel();
        _4ParamFieldsRow2LabelC = new javax.swing.JLabel();
        _4ParamFieldsRow2LabelD = new javax.swing.JLabel();
        _4ParamFieldsRow2TextFieldA = new javax.swing.JTextField();
        _4ParamFieldsRow2TextFieldB = new javax.swing.JTextField();
        _4ParamFieldsRow2TextFieldC = new javax.swing.JTextField();
        _4ParamFieldsRow2TextFieldD = new javax.swing.JTextField();
        zoneHemiPanel = new javax.swing.JPanel();
        zoneBoxPanel = new javax.swing.JPanel();
        zoneRadioButton = new javax.swing.JRadioButton();
        zoneLabel = new javax.swing.JLabel();
        zoneTextField = new javax.swing.JTextField();
        tempZoneBoxLabel = new javax.swing.JLabel();
        zoneRangeLabel = new javax.swing.JLabel();
        hemiBoxPanel = new javax.swing.JPanel();
        nHemiRadioButton = new javax.swing.JRadioButton();
        sHemiRadioButton = new javax.swing.JRadioButton();

        setLayout(new java.awt.GridBagLayout());

        setAlignmentX(1.0F);
        setAlignmentY(1.0F);
        setMinimumSize(new java.awt.Dimension(463, 268));
        setPreferredSize(new java.awt.Dimension(463, 268));
        datumPanel.setLayout(new java.awt.GridBagLayout());

        datumPanel.setMinimumSize(new java.awt.Dimension(460, 40));
        datumPanel.setPreferredSize(new java.awt.Dimension(460, 40));
        datumLabel.setText("Datum:");
        datumLabel.setMaximumSize(new java.awt.Dimension(270, 16));
        datumLabel.setMinimumSize(new java.awt.Dimension(270, 16));
        datumLabel.setPreferredSize(new java.awt.Dimension(270, 16));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 9);
        datumPanel.add(datumLabel, gridBagConstraints);

        ellipsoidLabel.setText("Ellipsoid:");
        ellipsoidLabel.setMaximumSize(new java.awt.Dimension(172, 16));
        ellipsoidLabel.setMinimumSize(new java.awt.Dimension(172, 16));
        ellipsoidLabel.setPreferredSize(new java.awt.Dimension(172, 16));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHEAST;
        gridBagConstraints.insets = new java.awt.Insets(0, 7, 0, 0);
        datumPanel.add(ellipsoidLabel, gridBagConstraints);

        datumSelectLayeredPane.setMinimumSize(new java.awt.Dimension(270, 20));
        datumTextField.setEditable(false);
        datumTextField.setText("jTextField1");
        datumTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        datumTextField.setMinimumSize(new java.awt.Dimension(320, 20));
        datumTextField.setPreferredSize(new java.awt.Dimension(320, 20));
        datumTextField.setBounds(0, 0, 270, 20);
        datumSelectLayeredPane.add(datumTextField, javax.swing.JLayeredPane.DEFAULT_LAYER);

        datumComboBox.setMinimumSize(new java.awt.Dimension(320, 20));
        datumComboBox.setPreferredSize(new java.awt.Dimension(320, 20));
        datumComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                datumComboBoxActionPerformed(evt);
            }
        });

        datumComboBox.setBounds(0, 0, 270, 20);
        datumSelectLayeredPane.add(datumComboBox, javax.swing.JLayeredPane.DEFAULT_LAYER);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.SOUTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 9);
        datumPanel.add(datumSelectLayeredPane, gridBagConstraints);

        ellipsoidTextField.setEditable(false);
        ellipsoidTextField.setText("jTextField2");
        ellipsoidTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        ellipsoidTextField.setMinimumSize(new java.awt.Dimension(172, 20));
        ellipsoidTextField.setPreferredSize(new java.awt.Dimension(172, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.SOUTHEAST;
        gridBagConstraints.insets = new java.awt.Insets(0, 7, 0, 0);
        datumPanel.add(ellipsoidTextField, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(1, 2, 1, 2);
        add(datumPanel, gridBagConstraints);

        projectionPanel.setLayout(new java.awt.GridBagLayout());

        projectionPanel.setMinimumSize(new java.awt.Dimension(460, 31));
        projectionPanel.setPreferredSize(new java.awt.Dimension(460, 31));
        inputProjectionLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        inputProjectionLabel.setText("jLabel7");
        projectionPanel.add(inputProjectionLabel, new java.awt.GridBagConstraints());

        projectionComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                projectionComboBoxActionPerformed(evt);
            }
        });

        projectionPanel.add(projectionComboBox, new java.awt.GridBagConstraints());

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 1, 2);
        add(projectionPanel, gridBagConstraints);

        paramFieldsRow1LayeredPane.setMaximumSize(new java.awt.Dimension(460, 40));
        paramFieldsRow1LayeredPane.setMinimumSize(new java.awt.Dimension(460, 40));
        _3ParamFieldsRow1Panel.setLayout(new java.awt.GridLayout(2, 3, 12, 0));

        _3ParamFieldsRow1Panel.setMaximumSize(new java.awt.Dimension(460, 40));
        _3ParamFieldsRow1Panel.setMinimumSize(new java.awt.Dimension(460, 40));
        _3ParamFieldsRow1Panel.setOpaque(false);
        _3ParamFieldsRow1Panel.setPreferredSize(new java.awt.Dimension(460, 40));
        _3ParamFieldsRow1LabelA.setText("Longitude");
        _3ParamFieldsRow1LabelA.setMaximumSize(new java.awt.Dimension(105, 16));
        _3ParamFieldsRow1LabelA.setMinimumSize(new java.awt.Dimension(105, 16));
        _3ParamFieldsRow1LabelA.setPreferredSize(new java.awt.Dimension(105, 16));
        _3ParamFieldsRow1LabelA.setOpaque(true);
        _3ParamFieldsRow1Panel.add(_3ParamFieldsRow1LabelA);

        _3ParamFieldsRow1LabelB.setText("Latitude");
        _3ParamFieldsRow1LabelB.setMaximumSize(new java.awt.Dimension(105, 16));
        _3ParamFieldsRow1LabelB.setMinimumSize(new java.awt.Dimension(105, 16));
        _3ParamFieldsRow1LabelB.setPreferredSize(new java.awt.Dimension(105, 16));
        _3ParamFieldsRow1LabelB.setOpaque(true);
        _3ParamFieldsRow1Panel.add(_3ParamFieldsRow1LabelB);

        _3ParamFieldsRow1LabelC.setText("Scale Factor");
        _3ParamFieldsRow1LabelC.setMaximumSize(new java.awt.Dimension(105, 16));
        _3ParamFieldsRow1LabelC.setMinimumSize(new java.awt.Dimension(105, 16));
        _3ParamFieldsRow1LabelC.setPreferredSize(new java.awt.Dimension(105, 16));
        _3ParamFieldsRow1LabelC.setOpaque(true);
        _3ParamFieldsRow1Panel.add(_3ParamFieldsRow1LabelC);

        _3ParamFieldsRow1TextFieldA.setText("0 0 0.00E");
        _3ParamFieldsRow1TextFieldA.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _3ParamFieldsRow1TextFieldA.setMinimumSize(new java.awt.Dimension(138, 20));
        _3ParamFieldsRow1TextFieldA.setPreferredSize(new java.awt.Dimension(138, 20));
        _3ParamFieldsRow1Panel.add(_3ParamFieldsRow1TextFieldA);

        _3ParamFieldsRow1TextFieldB.setText("0 0 0.0N");
        _3ParamFieldsRow1TextFieldB.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _3ParamFieldsRow1TextFieldB.setMinimumSize(new java.awt.Dimension(138, 20));
        _3ParamFieldsRow1TextFieldB.setPreferredSize(new java.awt.Dimension(138, 20));
        _3ParamFieldsRow1Panel.add(_3ParamFieldsRow1TextFieldB);

        _3ParamFieldsRow1TextFieldC.setText("1.00000");
        _3ParamFieldsRow1TextFieldC.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _3ParamFieldsRow1TextFieldC.setMinimumSize(new java.awt.Dimension(138, 20));
        _3ParamFieldsRow1TextFieldC.setPreferredSize(new java.awt.Dimension(138, 20));
        _3ParamFieldsRow1Panel.add(_3ParamFieldsRow1TextFieldC);

        _3ParamFieldsRow1Panel.setBounds(4, 2, 460, 40);
        paramFieldsRow1LayeredPane.add(_3ParamFieldsRow1Panel, javax.swing.JLayeredPane.DEFAULT_LAYER);

        _4ParamFieldsRow1Panel.setLayout(new java.awt.GridLayout(2, 4, 12, 0));

        _4ParamFieldsRow1Panel.setMinimumSize(new java.awt.Dimension(1, 1));
        _4ParamFieldsRow1Panel.setPreferredSize(new java.awt.Dimension(466, 40));
        _4ParamFieldsRow1LabelA.setText("Latitude");
        _4ParamFieldsRow1LabelA.setMinimumSize(new java.awt.Dimension(4, 10));
        _4ParamFieldsRow1Panel.add(_4ParamFieldsRow1LabelA);

        _4ParamFieldsRow1LabelB.setText("Longitude");
        _4ParamFieldsRow1LabelB.setMinimumSize(new java.awt.Dimension(4, 10));
        _4ParamFieldsRow1Panel.add(_4ParamFieldsRow1LabelB);

        _4ParamFieldsRow1LabelC.setText("False Easting");
        _4ParamFieldsRow1LabelC.setMinimumSize(new java.awt.Dimension(4, 10));
        _4ParamFieldsRow1LabelC.setPreferredSize(new java.awt.Dimension(66, 16));
        _4ParamFieldsRow1Panel.add(_4ParamFieldsRow1LabelC);

        _4ParamFieldsRow1LabelD.setText("False Northing");
        _4ParamFieldsRow1LabelD.setMinimumSize(new java.awt.Dimension(4, 10));
        _4ParamFieldsRow1Panel.add(_4ParamFieldsRow1LabelD);

        _4ParamFieldsRow1TextFieldA.setText("0 0 0.00N");
        _4ParamFieldsRow1TextFieldA.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _4ParamFieldsRow1Panel.add(_4ParamFieldsRow1TextFieldA);

        _4ParamFieldsRow1TextFieldB.setText("0 0 0.00W");
        _4ParamFieldsRow1TextFieldB.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _4ParamFieldsRow1TextFieldB.setMinimumSize(new java.awt.Dimension(4, 10));
        _4ParamFieldsRow1Panel.add(_4ParamFieldsRow1TextFieldB);

        _4ParamFieldsRow1TextFieldC.setText("200000");
        _4ParamFieldsRow1TextFieldC.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _4ParamFieldsRow1TextFieldC.setMinimumSize(new java.awt.Dimension(4, 10));
        _4ParamFieldsRow1TextFieldC.setPreferredSize(new java.awt.Dimension(40, 20));
        _4ParamFieldsRow1Panel.add(_4ParamFieldsRow1TextFieldC);

        _4ParamFieldsRow1TextFieldD.setText("400000");
        _4ParamFieldsRow1TextFieldD.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _4ParamFieldsRow1TextFieldD.setMinimumSize(new java.awt.Dimension(4, 10));
        _4ParamFieldsRow1Panel.add(_4ParamFieldsRow1TextFieldD);

        _4ParamFieldsRow1Panel.setBounds(4, 2, 460, 40);
        paramFieldsRow1LayeredPane.add(_4ParamFieldsRow1Panel, javax.swing.JLayeredPane.DEFAULT_LAYER);

        neysParamsRow1Panel.setLayout(new java.awt.GridBagLayout());

        neysParamsRow1Panel.setMinimumSize(new java.awt.Dimension(461, 55));
        neysParamsRow1Panel.setPreferredSize(new java.awt.Dimension(461, 55));
        centralMeridianNeysParamsPanel.setLayout(new java.awt.GridLayout(2, 1, 12, 0));

        centralMeridianNeysParamsPanel.setMinimumSize(new java.awt.Dimension(106, 36));
        centralMeridianNeysParamsPanel.setPreferredSize(new java.awt.Dimension(106, 36));
        centralMeridianNeysParamsLabel.setText("Central Meridian:");
        centralMeridianNeysParamsLabel.setMinimumSize(new java.awt.Dimension(4, 10));
        centralMeridianNeysParamsPanel.add(centralMeridianNeysParamsLabel);

        centralMeridianNeysParamsTextField.setText("0 0 0.00E");
        centralMeridianNeysParamsTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        centralMeridianNeysParamsTextField.setMinimumSize(new java.awt.Dimension(4, 10));
        centralMeridianNeysParamsPanel.add(centralMeridianNeysParamsTextField);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 6);
        neysParamsRow1Panel.add(centralMeridianNeysParamsPanel, gridBagConstraints);

        originLatitudeNeysParamsPanel.setLayout(new java.awt.GridLayout(2, 1, 12, 0));

        originLatitudeNeysParamsPanel.setMinimumSize(new java.awt.Dimension(106, 36));
        originLatitudeNeysParamsPanel.setPreferredSize(new java.awt.Dimension(106, 36));
        originLatitudeNeysParamsLabel.setText("Origin Latitude:");
        originLatitudeNeysParamsLabel.setMinimumSize(new java.awt.Dimension(4, 10));
        originLatitudeNeysParamsPanel.add(originLatitudeNeysParamsLabel);

        originLatitudeNeysParamsTextField.setText("0 0 0.00N");
        originLatitudeNeysParamsTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        originLatitudeNeysParamsTextField.setMinimumSize(new java.awt.Dimension(4, 10));
        originLatitudeNeysParamsPanel.add(originLatitudeNeysParamsTextField);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(0, 6, 0, 6);
        neysParamsRow1Panel.add(originLatitudeNeysParamsPanel, gridBagConstraints);

        stdParallel1NeysParamsPanel.setLayout(new java.awt.GridBagLayout());

        stdParallel1NeysParamsPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(null, "Std. Parallel 1:", javax.swing.border.TitledBorder.CENTER, javax.swing.border.TitledBorder.DEFAULT_POSITION));
        stdParallel1NeysParamsPanel.setAlignmentX(0.0F);
        stdParallel1NeysParamsPanel.setAlignmentY(0.0F);
        stdParallel1NeysParamsPanel.setMaximumSize(new java.awt.Dimension(107, 39));
        stdParallel1NeysParamsPanel.setMinimumSize(new java.awt.Dimension(107, 39));
        stdParallel1NeysParamsPanel.setPreferredSize(new java.awt.Dimension(107, 39));
        neys71RadioButton.setText("71");
        neys71RadioButton.setAlignmentY(0.0F);
        neys71RadioButton.setHorizontalTextPosition(javax.swing.SwingConstants.RIGHT);
        neys71RadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        neys71RadioButton.setMaximumSize(new java.awt.Dimension(30, 17));
        neys71RadioButton.setMinimumSize(new java.awt.Dimension(30, 17));
        neys71RadioButton.setModel(nHemiRadioButton.getModel());
        neys71RadioButton.setPreferredSize(new java.awt.Dimension(40, 17));
        neys71RadioButton.setVerticalAlignment(javax.swing.SwingConstants.TOP);
        neys71RadioButton.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
        gridBagConstraints.ipadx = 9;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 5, 5, 0);
        stdParallel1NeysParamsPanel.add(neys71RadioButton, gridBagConstraints);

        neys74RadioButton.setText("74");
        neys74RadioButton.setAlignmentY(0.0F);
        neys74RadioButton.setHorizontalTextPosition(javax.swing.SwingConstants.RIGHT);
        neys74RadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        neys74RadioButton.setMaximumSize(new java.awt.Dimension(30, 17));
        neys74RadioButton.setMinimumSize(new java.awt.Dimension(30, 17));
        neys74RadioButton.setModel(sHemiRadioButton.getModel());
        neys74RadioButton.setPreferredSize(new java.awt.Dimension(40, 17));
        neys74RadioButton.setVerticalAlignment(javax.swing.SwingConstants.TOP);
        neys74RadioButton.setVerticalTextPosition(javax.swing.SwingConstants.TOP);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
        gridBagConstraints.ipadx = 10;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHEAST;
        gridBagConstraints.insets = new java.awt.Insets(0, 2, 5, 0);
        stdParallel1NeysParamsPanel.add(neys74RadioButton, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
        gridBagConstraints.insets = new java.awt.Insets(0, 6, 0, 6);
        neysParamsRow1Panel.add(stdParallel1NeysParamsPanel, gridBagConstraints);

        stdParallel2NeysParamsPanel.setLayout(new java.awt.GridLayout(2, 1, 12, 0));

        stdParallel2NeysParamsPanel.setMinimumSize(new java.awt.Dimension(106, 36));
        stdParallel2NeysParamsPanel.setPreferredSize(new java.awt.Dimension(106, 36));
        stdParallel2NeysParamsLabel.setText("Std. Parallel 2:");
        stdParallel2NeysParamsLabel.setMinimumSize(new java.awt.Dimension(4, 10));
        stdParallel2NeysParamsPanel.add(stdParallel2NeysParamsLabel);

        stdParallel2NeysParamsTextField.setEditable(false);
        stdParallel2NeysParamsTextField.setText("89 59 59.0");
        stdParallel2NeysParamsTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        stdParallel2NeysParamsTextField.setMinimumSize(new java.awt.Dimension(4, 10));
        stdParallel2NeysParamsPanel.add(stdParallel2NeysParamsTextField);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(0, 6, 0, 0);
        neysParamsRow1Panel.add(stdParallel2NeysParamsPanel, gridBagConstraints);

        neysParamsRow1Panel.setBounds(0, 2, 460, 40);
        paramFieldsRow1LayeredPane.add(neysParamsRow1Panel, javax.swing.JLayeredPane.DEFAULT_LAYER);

        heightLabelPanel.setLayout(new java.awt.GridBagLayout());

        heightLabelPanel.setMinimumSize(new java.awt.Dimension(213, 20));
        heightLabelPanel.setPreferredSize(new java.awt.Dimension(213, 20));
        heightLabel.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        heightLabel.setText("jLabel3");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTH;
        heightLabelPanel.add(heightLabel, gridBagConstraints);

        heightLabelPanel.setBounds(4, 2, 460, 40);
        paramFieldsRow1LayeredPane.add(heightLabelPanel, javax.swing.JLayeredPane.DEFAULT_LAYER);

        heightPanel.setLayout(new java.awt.GridBagLayout());

        heightPanel.setAlignmentX(0.0F);
        heightPanel.setAlignmentY(0.0F);
        heightPanel.setMinimumSize(new java.awt.Dimension(469, 50));
        heightPanel.setOpaque(false);
        heightPanel.setPreferredSize(new java.awt.Dimension(469, 50));
        heightComboBox.setMinimumSize(new java.awt.Dimension(276, 21));
        heightComboBox.setPreferredSize(new java.awt.Dimension(276, 21));
        heightComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                heightComboBoxActionPerformed(evt);
            }
        });

        heightPanel.add(heightComboBox, new java.awt.GridBagConstraints());

        heightPanel.setBounds(0, 0, 462, 45);
        paramFieldsRow1LayeredPane.add(heightPanel, javax.swing.JLayeredPane.DEFAULT_LAYER);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.insets = new java.awt.Insets(2, 2, 1, 2);
        add(paramFieldsRow1LayeredPane, gridBagConstraints);

        paramFieldsRow2LayeredPane.setMinimumSize(new java.awt.Dimension(460, 55));
        _3ParamFieldsRow2Panel.setLayout(new java.awt.GridLayout(2, 3, 12, 0));

        _3ParamFieldsRow2Panel.setOpaque(false);
        _3ParamFieldsRow2LabelA.setText("Latitude");
        _3ParamFieldsRow2LabelA.setOpaque(true);
        _3ParamFieldsRow2Panel.add(_3ParamFieldsRow2LabelA);

        _3ParamFieldsRow2LabelB.setText("Longitude");
        _3ParamFieldsRow2LabelB.setOpaque(true);
        _3ParamFieldsRow2Panel.add(_3ParamFieldsRow2LabelB);

        _3ParamFieldsRow2LabelC.setText("Scale Factor");
        _3ParamFieldsRow2LabelC.setOpaque(true);
        _3ParamFieldsRow2Panel.add(_3ParamFieldsRow2LabelC);

        _3ParamFieldsRow2TextFieldA.setText("0 0 0.00S");
        _3ParamFieldsRow2TextFieldA.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _3ParamFieldsRow2Panel.add(_3ParamFieldsRow2TextFieldA);

        _3ParamFieldsRow2TextFieldB.setText("0 0 0.0E");
        _3ParamFieldsRow2TextFieldB.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _3ParamFieldsRow2Panel.add(_3ParamFieldsRow2TextFieldB);

        _3ParamFieldsRow2TextFieldC.setText("4500");
        _3ParamFieldsRow2TextFieldC.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _3ParamFieldsRow2Panel.add(_3ParamFieldsRow2TextFieldC);

        _3ParamFieldsRow2Panel.setBounds(0, 0, 462, 38);
        paramFieldsRow2LayeredPane.add(_3ParamFieldsRow2Panel, javax.swing.JLayeredPane.DEFAULT_LAYER);

        _4ParamFieldsRow2Panel.setLayout(new java.awt.GridLayout(2, 4, 12, 0));

        _4ParamFieldsRow2Panel.setMinimumSize(new java.awt.Dimension(460, 40));
        _4ParamFieldsRow2Panel.setPreferredSize(new java.awt.Dimension(460, 40));
        _4ParamFieldsRow2LabelA.setText("Latitude");
        _4ParamFieldsRow2LabelA.setMaximumSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2LabelA.setMinimumSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2LabelA.setPreferredSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2Panel.add(_4ParamFieldsRow2LabelA);

        _4ParamFieldsRow2LabelB.setText("Longitude");
        _4ParamFieldsRow2LabelB.setMaximumSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2LabelB.setMinimumSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2LabelB.setPreferredSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2Panel.add(_4ParamFieldsRow2LabelB);

        _4ParamFieldsRow2LabelC.setText("False Easting");
        _4ParamFieldsRow2LabelC.setMaximumSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2LabelC.setMinimumSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2LabelC.setPreferredSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2Panel.add(_4ParamFieldsRow2LabelC);

        _4ParamFieldsRow2LabelD.setText("False Northing");
        _4ParamFieldsRow2LabelD.setMaximumSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2LabelD.setMinimumSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2LabelD.setPreferredSize(new java.awt.Dimension(100, 16));
        _4ParamFieldsRow2Panel.add(_4ParamFieldsRow2LabelD);

        _4ParamFieldsRow2TextFieldA.setText("0 0 0.00N");
        _4ParamFieldsRow2TextFieldA.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _4ParamFieldsRow2TextFieldA.setMinimumSize(new java.awt.Dimension(100, 20));
        _4ParamFieldsRow2TextFieldA.setPreferredSize(new java.awt.Dimension(100, 20));
        _4ParamFieldsRow2Panel.add(_4ParamFieldsRow2TextFieldA);

        _4ParamFieldsRow2TextFieldB.setText("0 0 0.00W");
        _4ParamFieldsRow2TextFieldB.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _4ParamFieldsRow2TextFieldB.setMinimumSize(new java.awt.Dimension(100, 20));
        _4ParamFieldsRow2TextFieldB.setPreferredSize(new java.awt.Dimension(100, 20));
        _4ParamFieldsRow2Panel.add(_4ParamFieldsRow2TextFieldB);

        _4ParamFieldsRow2TextFieldC.setText("200000");
        _4ParamFieldsRow2TextFieldC.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _4ParamFieldsRow2TextFieldC.setMinimumSize(new java.awt.Dimension(100, 20));
        _4ParamFieldsRow2TextFieldC.setPreferredSize(new java.awt.Dimension(100, 20));
        _4ParamFieldsRow2Panel.add(_4ParamFieldsRow2TextFieldC);

        _4ParamFieldsRow2TextFieldD.setText("400000");
        _4ParamFieldsRow2TextFieldD.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        _4ParamFieldsRow2TextFieldD.setMinimumSize(new java.awt.Dimension(100, 20));
        _4ParamFieldsRow2TextFieldD.setPreferredSize(new java.awt.Dimension(100, 20));
        _4ParamFieldsRow2Panel.add(_4ParamFieldsRow2TextFieldD);

        _4ParamFieldsRow2Panel.setBounds(4, 2, 460, 40);
        paramFieldsRow2LayeredPane.add(_4ParamFieldsRow2Panel, javax.swing.JLayeredPane.DEFAULT_LAYER);

        zoneHemiPanel.setLayout(new java.awt.GridBagLayout());

        zoneHemiPanel.setMinimumSize(new java.awt.Dimension(220, 60));
        zoneHemiPanel.setPreferredSize(new java.awt.Dimension(220, 60));
        zoneHemiPanel.setOpaque(false);
        zoneBoxPanel.setLayout(new java.awt.GridBagLayout());

        zoneBoxPanel.setMinimumSize(new java.awt.Dimension(175, 58));
        zoneBoxPanel.setPreferredSize(new java.awt.Dimension(175, 58));
        zoneRadioButton.setText("Override:");
        zoneRadioButton.setActionCommand("( set )");
        zoneRadioButton.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);
        zoneRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        zoneRadioButton.setVerticalAlignment(javax.swing.SwingConstants.TOP);
        zoneRadioButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                zoneActionPerformed(evt);
            }
        });

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 8);
        zoneBoxPanel.add(zoneRadioButton, gridBagConstraints);

        zoneLabel.setText("Zone");
        zoneLabel.setOpaque(true);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        zoneBoxPanel.add(zoneLabel, gridBagConstraints);

        zoneTextField.setHorizontalAlignment(javax.swing.JTextField.LEFT);
        zoneTextField.setText("0");
        zoneTextField.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.LOWERED));
        zoneTextField.setMinimumSize(new java.awt.Dimension(35, 19));
        zoneTextField.setPreferredSize(new java.awt.Dimension(41, 19));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 11, 0);
        zoneBoxPanel.add(zoneTextField, gridBagConstraints);

        tempZoneBoxLabel.setOpaque(true);
        zoneBoxPanel.add(tempZoneBoxLabel, new java.awt.GridBagConstraints());

        zoneRangeLabel.setText("(1-60):");
        zoneRangeLabel.setOpaque(true);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        zoneBoxPanel.add(zoneRangeLabel, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 5);
        zoneHemiPanel.add(zoneBoxPanel, gridBagConstraints);

        hemiBoxPanel.setLayout(new java.awt.GridBagLayout());

        hemiBoxPanel.setBorder(javax.swing.BorderFactory.createTitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER, javax.swing.border.TitledBorder.DEFAULT_POSITION));
        hemiBoxPanel.setMaximumSize(new java.awt.Dimension(101, 45));
        hemiBoxPanel.setMinimumSize(new java.awt.Dimension(101, 45));
        hemiBoxPanel.setPreferredSize(new java.awt.Dimension(101, 45));
        nHemiRadioButton.setText("N");
        nHemiRadioButton.setHorizontalTextPosition(javax.swing.SwingConstants.RIGHT);
        nHemiRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        nHemiRadioButton.setMaximumSize(new java.awt.Dimension(28, 20));
        nHemiRadioButton.setModel(nHemiRadioButton.getModel());
        nHemiRadioButton.setPreferredSize(new java.awt.Dimension(28, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 5, 7);
        hemiBoxPanel.add(nHemiRadioButton, gridBagConstraints);

        sHemiRadioButton.setText("S");
        sHemiRadioButton.setHorizontalTextPosition(javax.swing.SwingConstants.RIGHT);
        sHemiRadioButton.setMargin(new java.awt.Insets(0, 0, 0, 0));
        sHemiRadioButton.setMaximumSize(new java.awt.Dimension(28, 20));
        sHemiRadioButton.setModel(sHemiRadioButton.getModel());
        sHemiRadioButton.setPreferredSize(new java.awt.Dimension(28, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
        gridBagConstraints.insets = new java.awt.Insets(0, 7, 5, 0);
        hemiBoxPanel.add(sHemiRadioButton, gridBagConstraints);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        gridBagConstraints.insets = new java.awt.Insets(14, 0, 4, 55);
        zoneHemiPanel.add(hemiBoxPanel, gridBagConstraints);

        zoneHemiPanel.setBounds(0, 0, 462, 55);
        paramFieldsRow2LayeredPane.add(zoneHemiPanel, javax.swing.JLayeredPane.DEFAULT_LAYER);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.insets = new java.awt.Insets(1, 2, 1, 2);
        add(paramFieldsRow2LayeredPane, gridBagConstraints);

    }// </editor-fold>//GEN-END:initComponents

    private void heightComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_heightComboBoxActionPerformed
 heightType = heightComboBox.getSelectedIndex();
 if( state != ConversionState.FILE )
 {
     if(heightComboBox.getSelectedIndex() == HeightType.NO_HEIGHT)
        setHeightFieldEditable(false);
     else
        setHeightFieldEditable(true);
 }
    }//GEN-LAST:event_heightComboBoxActionPerformed

  private void zoneActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_zoneActionPerformed
    if (zoneRadioButton.isSelected() == true)
      override = 1;
    else if (zoneRadioButton.isSelected() == false)
      override = 0;
    return;
  }//GEN-LAST:event_zoneActionPerformed

  private void projectionComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_projectionComboBoxActionPerformed
    projectionType = CoordinateTypes.index((java.lang.String)projectionComboBox.getSelectedItem());
    createMasterPanel();
    if (state != ConversionState.FILE)
    {
        coordPanel.createCoordPanel(projectionType);
        if (parent!= null)
            parent.checkValidConversion();
    }
    if (parent != null)
        parent.check3DConversion();
  }//GEN-LAST:event_projectionComboBoxActionPerformed

  private void datumComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_datumComboBoxActionPerformed
    try
    {
        datumIndex = datumComboBox.getSelectedIndex() + 1; 
        if(datumIndex == 0)
          datumIndex = 1;
        java.lang.String datumEllipsoidCode = jniEngine.JNIGetDatumEllipsoidCode(datumIndex);
        long inputEllipsoidIndex = jniEngine.JNIGetEllipsoidIndex(datumEllipsoidCode);
        java.lang.String inputEllipsoidName = jniEngine.JNIGetEllipsoidName(inputEllipsoidIndex);
        ellipsoidTextField.setText(datumEllipsoidCode + ":  " +  inputEllipsoidName);
        ellipsoidTextField.setCaretPosition(0);
        if (parent!= null)
            parent.checkValidConversion();

    }
    catch(GeotransError e)
    {
        jniStrtoval.displayErrorMsg(this, e.getMessage());
    }
    catch(JNIException e)
    {
        jniStrtoval.displayErrorMsg(this, e.getMessage());
    }
  }//GEN-LAST:event_datumComboBoxActionPerformed


    private void initFileInputPanel()
    {
        java.lang.String msg[] = new java.lang.String[12];

        datumComboBox.setVisible(false);
        projectionComboBox.setVisible(false);

        try
        {
            int inputFileType = jniEngine.JNIGetCoordinateSystem(state, direction);

            long inputDatumIndex = jniEngine.JNIGetDatum(state, direction);
            java.lang.String inputDatumCode = jniEngine.JNIGetDatumCode(inputDatumIndex);
            java.lang.String inputDatumName = jniEngine.JNIGetDatumName(inputDatumIndex);
            datumTextField.setText(inputDatumCode + ":  " +  inputDatumName);

            java.lang.String datumEllipsoidCode = jniEngine.JNIGetDatumEllipsoidCode(inputDatumIndex);
            long inputEllipsoidIndex = jniEngine.JNIGetEllipsoidIndex(datumEllipsoidCode);
            java.lang.String inputEllipsoidName = jniEngine.JNIGetEllipsoidName(inputEllipsoidIndex);
            ellipsoidTextField.setText(datumEllipsoidCode + ":  " +  inputEllipsoidName);

            switch(inputFileType)
            {
                case CoordinateTypes.ALBERS:
                {
                    inputProjectionLabel.setText("Albers Equal Area Conic Projection");
                    AlbersEqualAreaConic albersParams = jniEngine.JNIGetAlbersEqualAreaConicParams(state, direction);
                    setSixParams();
                    setSixParamsUnedit();
                    _4ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(albersParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(albersParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(albersParams.getStdParallel1()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(albersParams.getStdParallel2()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(albersParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(albersParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.AZIMUTHAL:
                {
                    inputProjectionLabel.setText("Azimuthal Equidistant Projection");
                    AzimuthalEquidistant azeqParams = jniEngine.JNIGetAzimuthalEquidistantParams(state, direction);
                    setFourParams();
                    setFourParamsUnedit();
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(azeqParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(azeqParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(azeqParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(azeqParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.BNG:
                {
                    inputProjectionLabel.setText("British National Grid Coordinates");
                    hideParams();
                    break;
                }
                case CoordinateTypes.BONNE:
                {
                    inputProjectionLabel.setText("Bonne Projection");
                    Bonne bonneParams = jniEngine.JNIGetBonneParams(state, direction);
                    setFourParams();
                    setFourParamsUnedit();
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(bonneParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(bonneParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(bonneParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(bonneParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.CASSINI:
                {
                    inputProjectionLabel.setText("Cassini Projection");
                    Cassini cassiniParams = jniEngine.JNIGetCassiniParams(state, direction);
                    setFourParams();
                    setFourParamsUnedit();
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(cassiniParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(cassiniParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(cassiniParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(cassiniParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.CYLEQA:
                {
                    inputProjectionLabel.setText("Cylindrical Equal Area Projection");
                    CylindricalEqualArea cyleqaParams = jniEngine.JNIGetCylindricalEqualAreaParams(state, direction);
                    setFourParams();
                    setFourParamsUnedit();
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(cyleqaParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(cyleqaParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(cyleqaParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(cyleqaParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.ECKERT4:
                {
                    inputProjectionLabel.setText("Eckert IV Projection");
                    Eckert4 eckert4Params = jniEngine.JNIGetEckert4Params(state, direction);
                    setThreeParams();
                    setThreeParamsUnedit();
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(eckert4Params.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(eckert4Params.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(eckert4Params.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.ECKERT6:
                {
                    inputProjectionLabel.setText("Eckert VI Projection");
                    Eckert6 eckert6Params = jniEngine.JNIGetEckert6Params(state, direction);
                    setThreeParams();
                    setThreeParamsUnedit();
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(eckert6Params.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(eckert6Params.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(eckert6Params.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.EQDCYL:
                {
                    inputProjectionLabel.setText("Equidistant Cylindrical");
                    EquidistantCylindrical eqdcylParams = jniEngine.JNIGetEquidistantCylindricalParams(state, direction);
                    setFourParams();
                    _4ParamFieldsRow1LabelC.setText("Standard Parallel:");
                    setFourParamsUnedit();
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(eqdcylParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(eqdcylParams.getStdParallel()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(eqdcylParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(eqdcylParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.GARS:
                {
                    inputProjectionLabel.setText("GARS Coordinates");
                    hideParams();
                    break;
                }
                case CoordinateTypes.GEOCENTRIC:
                {
                    inputProjectionLabel.setText("Geocentric Coordinates");
                    hideParams();
                    break;
                }
                case CoordinateTypes.GEODETIC:
                {
                    inputProjectionLabel.setText("Geodetic Coordinates");
                    Geodetic geodeticParams = jniEngine.JNIGetGeodeticParams(state, direction);
                    hideParams();
                    heightLabelPanel.setVisible(true);
                    paramFieldsRow1LayeredPane.moveToFront(heightLabelPanel);
                    int height_Type = geodeticParams.getHeightType();
                    if (height_Type == HeightType.MSL_EGM96_15M_BL_HEIGHT)
                        heightLabel.setText("MSL-EGM96-15M-BL Height");
                    else if (height_Type == HeightType.MSL_EGM96_VG_NS_HEIGHT)
                        heightLabel.setText("MSL-EGM96-VG-NS Height");
                    else if (height_Type == HeightType.MSL_EGM84_10D_BL_HEIGHT)
                        heightLabel.setText("MSL-EGM84-10D-BL Height");
                    else if (height_Type == HeightType.MSL_EGM84_10D_NS_HEIGHT)
                        heightLabel.setText("MSL-EGM84-10D-NS Height");
                    else if (height_Type == HeightType.NO_HEIGHT)
                        heightLabel.setText("No Height");
                    else
                        heightLabel.setText("Ellipsoid Height");
                   break;
                }
                case CoordinateTypes.GEOREF:
                {
                    inputProjectionLabel.setText("GEOREF Coordinates");
                    hideParams();
                    break;
                }
                case CoordinateTypes.GNOMONIC:
                {
                    inputProjectionLabel.setText("Gnomonic Projection");
                    Gnomonic gnomonicParams = jniEngine.JNIGetGnomonicParams(state, direction);
                    setFourParams();
                    setFourParamsUnedit();
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(gnomonicParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(gnomonicParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(gnomonicParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(gnomonicParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.LAMBERT_1:
                {
                    inputProjectionLabel.setText("Lambert Conformal Conic (1 parallel) Projection");
                    LambertConformalConic1 lambert1Params = jniEngine.JNIGetLambertConformalConic1Params(state, direction);
                    setFiveParams();
                    setFiveParamsUnedit();
                    _3ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(lambert1Params.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(lambert1Params.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));

                    jniStrtoval.setNumberFormat(_3ParamFieldsRow1TextFieldC, lambert1Params.getScaleFactor(), 5);

                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(lambert1Params.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(lambert1Params.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.LAMBERT_2:
                {
                    inputProjectionLabel.setText("Lambert Conformal Conic (2 parallel) Projection");
                    LambertConformalConic2 lambert2Params = jniEngine.JNIGetLambertConformalConic2Params(state, direction);
                    setSixParams();
                    setSixParamsUnedit();
                    _4ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(lambert2Params.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(lambert2Params.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(lambert2Params.getStdParallel1()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(lambert2Params.getStdParallel2()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(lambert2Params.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(lambert2Params.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.LOCCART:
                {
                    inputProjectionLabel.setText("Local Cartesian Coordinates");
                    LocalCartesian loccartParams = jniEngine.JNIGetLocalCartesianParams(state, direction);
                    setLCFourParams();
                    setLCFourParamsUnedit();
                    _3ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(loccartParams.getOriginLongitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(loccartParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _3ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNIMeterToString(loccartParams.getOriginHeight()));
                    _3ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNILongitudeToString(loccartParams.getOrientation()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    break;
                }
                case CoordinateTypes.MERCATOR:
                {
                    inputProjectionLabel.setText("Mercator Projection");
                    jniEngine.JNIConvert(0); /* this is to update mercator scale factor */
                    Mercator mercatorParams = jniEngine.JNIGetMercatorParams(state, direction);
                    setFiveParams();
                    setFiveParamsUnedit();
                    _3ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(mercatorParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(mercatorParams.getLatitudeOfTrueScale()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));

                    _3ParamFieldsRow1LabelB.setText("Lat. of True Scale");
                    jniStrtoval.setNumberFormat(_3ParamFieldsRow1TextFieldC, mercatorParams.getScaleFactor(), 5);

                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(mercatorParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(mercatorParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.MGRS:
                {
                    inputProjectionLabel.setText("MGRS Coordinates");
                    hideParams();
                    break;
                }
                case CoordinateTypes.MILLER:
                {
                    inputProjectionLabel.setText("Miller Cylindrical Projection");
                    MillerCylindrical millerParams = jniEngine.JNIGetMillerCylindricalParams(state, direction);
                    setThreeParams();
                    setThreeParamsUnedit();
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(millerParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(millerParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(millerParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.MOLLWEIDE:
                {
                    inputProjectionLabel.setText("Mollweide Projection");
                    Mollweide mollweidParams = jniEngine.JNIGetMollweideParams(state, direction);
                    setThreeParams();
                    setThreeParamsUnedit();
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(mollweidParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(mollweidParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(mollweidParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.NEYS:
                {
                    boolean northHemi = true;
                    inputProjectionLabel.setText("Ney's (Modified Lambert Conformal Conic) Projection");
                    Neys neysParams = jniEngine.JNIGetNeysParams(state, direction);
                    setSixParams();
                    setSixParamsUnedit();
                    double olat = neysParams.getOriginLatitude();
                    if (olat < 0)
                        northHemi = false;
                    _4ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(neysParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(olat*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    if (northHemi)
                        _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(neysParams.getStdParallel1()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    else
                        _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(neysParams.getStdParallel1()*-180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    /* std parallel 2 = 89 59 58.0 */
                    if (northHemi)
                        _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(89.99944444444444, useNSEW, useMinutes, useSeconds));
                    else
                        _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(-89.99944444444444, useNSEW, useMinutes, useSeconds));
                    /* std parallel 2 = 89 59 59.0 
                    if (northHemi)
                        _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(89.99972222222222, useNSEW, useMinutes, useSeconds));
                    else
                        _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(-89.99972222222222, useNSEW, useMinutes, useSeconds));*/

                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(neysParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(neysParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.NZMG:
                {
                    inputProjectionLabel.setText("New Zealand Map Grid Projection");
                    hideParams();
                    break;
                }
                case CoordinateTypes.OMERC:
                {
                    inputProjectionLabel.setText("Oblique Mercator Projection");
                    ObliqueMercator omercParams = jniEngine.JNIGetObliqueMercatorParams(state, direction);
                    setEightParams();
                    setEightParamsUnedit();
                    _4ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILatitudeToString(omercParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));

                    jniStrtoval.setNumberFormat(_4ParamFieldsRow1TextFieldB, omercParams.getScaleFactor(), 5);

                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILongitudeToString(omercParams.getLongitude1()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(omercParams.getLatitude1()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldA.setText(jniStrtoval.JNILongitudeToString(omercParams.getLongitude2()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNILatitudeToString(omercParams.getLatitude2()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(omercParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldD.setText(jniStrtoval.JNIMeterToString(omercParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.ORTHOGRAPHIC:
                {
                    inputProjectionLabel.setText("Orthographic Projection");
                    Orthographic orthogrParams = jniEngine.JNIGetOrthographicParams(state, direction);
                    setFourParams();
                    setFourParamsUnedit();
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(orthogrParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(orthogrParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(orthogrParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(orthogrParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.POLARSTEREO:
                {
                    inputProjectionLabel.setText("Polar Stereographic Projection");
                    PolarStereographic polarstParams = jniEngine.JNIGetPolarStereographicParams(state, direction);
                    setFourParams();
                    _4ParamFieldsRow1LabelB.setText("Long. Down");
                    _4ParamFieldsRow1LabelC.setText("Lat. of True Scale");
                    setFourParamsUnedit();
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(polarstParams.getLongitudeDownFromPole()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(polarstParams.getLatitudeOfTrueScale()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(polarstParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(polarstParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.POLYCONIC:
                {
                    inputProjectionLabel.setText("Polyconic Projection");
                    Polyconic polyconParams = jniEngine.JNIGetPolyconicParams(state, direction);
                    setFourParams();
                    setFourParamsUnedit();
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(polyconParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(polyconParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(polyconParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(polyconParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.SINUSOIDAL:
                {
                    inputProjectionLabel.setText("Sinusoidal Projection");
                    Sinusoidal sinusoidParams = jniEngine.JNIGetSinusoidalParams(state, direction);
                    setThreeParams();
                    setThreeParamsUnedit();
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(sinusoidParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(sinusoidParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(sinusoidParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.STEREOGRAPHIC:
                {
                    inputProjectionLabel.setText("Stereographic Projection");
                    Stereographic stereogrParams = jniEngine.JNIGetStereographicParams(state, direction);
                    setFourParams();
                    setFourParamsUnedit();
                    _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(stereogrParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(stereogrParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(stereogrParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(stereogrParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.TRCYLEQA:
                {
                    inputProjectionLabel.setText("Transverse Cylindrical Equal Area Projection");
                    TransverseCylindricalEqualArea trcyleqaParams = jniEngine.JNIGetTransverseCylindricalEqualAreaParams(state, direction);
                    setFiveParams();
                    setFiveParamsUnedit();
                    _3ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(trcyleqaParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(trcyleqaParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));

                    jniStrtoval.setNumberFormat(_3ParamFieldsRow1TextFieldC, trcyleqaParams.getScaleFactor(), 5);

                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(trcyleqaParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(trcyleqaParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.TRANMERC:
                {
                    inputProjectionLabel.setText("Transverse Mercator Projection");
                    TransverseMercator tranmercParams = jniEngine.JNIGetTransverseMercatorParams(state, direction);
                    setFiveParams();
                    setFiveParamsUnedit();
                    _3ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(tranmercParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(tranmercParams.getOriginLatitude()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));

                    jniStrtoval.setNumberFormat(_3ParamFieldsRow1TextFieldC, tranmercParams.getScaleFactor(), 5);

                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(tranmercParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(tranmercParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.GRINTEN:
                {
                    inputProjectionLabel.setText("Van der Grinten Projection");
                    VanDerGrinten grintenParams = jniEngine.JNIGetVanDerGrintenParams(state, direction);
                    setThreeParams();
                    setThreeParamsUnedit();
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(grintenParams.getCentralMeridian()*180/jniStrtoval.PI, useNSEW, useMinutes, useSeconds));
                    _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(grintenParams.getFalseEasting()));
                    _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(grintenParams.getFalseNorthing()));
                    break;
                }
                case CoordinateTypes.UPS:
                {
                    inputProjectionLabel.setText("Universal Polar Stereographic (UPS) Projection");
                    hideParams();
                    break;
                }
                case CoordinateTypes.USNG:
                {
                    inputProjectionLabel.setText("USNG Coordinates");
                    hideParams();
                    break;
                }
                case CoordinateTypes.UTM:
                {
                    inputProjectionLabel.setText("Universal Transverse Mercator (UTM) Projection");
                    hideParams();
                    break;
                }
                default:
                    break;
            }
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        catch(GeotransWarning e)
        {
            jniStrtoval.displayWarningMsg(this, e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
    }


    private void initMasterPanel()
    {
        try
        {
            datumTextField.setVisible(false);
            inputProjectionLabel.setVisible(false);

            fillHeightList();
            datumList = new FillList(datumComboBox, ListType.DATUM);
            fillProjectionList();

            if ((direction == SourceOrTarget.TARGET) && (state == ConversionState.INTERACTIVE))
                projectionType = CoordinateTypes.UTM;
            else
                projectionType = CoordinateTypes.GEODETIC;

            jniEngine.JNISetCoordinateSystem(state, direction, projectionType);
            projectionComboBox.setSelectedItem(CoordinateTypes.name(projectionType));
            if (state == ConversionState.INTERACTIVE)
                coordPanel.createCoordPanel(projectionType);
            createButtonGroups();
            createMasterPanel();
        }
        catch (GeotransError e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
    }

    private void createMasterPanel()
    {
        setFormat();
        switch (projectionType)
        {
            case CoordinateTypes.GEODETIC:
            { // height type
                hideParams();
                setHeight();
                break;
            }
            case CoordinateTypes.BNG:
            case CoordinateTypes.F16GRS:
            case CoordinateTypes.GARS:
            case CoordinateTypes.GEOCENTRIC:
            case CoordinateTypes.GEOREF:
            case CoordinateTypes.MGRS:
            case CoordinateTypes.USNG:
            case CoordinateTypes.NZMG:
            {
                hideParams();
                break;
            }
            case CoordinateTypes.UPS:
            {
                if (state == ConversionState.INTERACTIVE)
                {
                    setZone_Hemi();
                    zoneHemiPanel.setBounds(90, 0, 462, 55);
                    zoneBoxPanel.setVisible(false);
                }
                else
                    hideParams();
                if (!Platform.isJavaV1_3)
                {
                    if (Platform.isUnix)
                    {
                    if (currLookAndFeel.equals("Java"))
                        hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                           javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 10), java.awt.Color.black));
                    else
                        hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                           javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 0, 10), java.awt.Color.black));
                    }
                    else
                    {
                        if (currLookAndFeel.equals("Java"))
                            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                                   javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 12)));
                        else
                            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                                   javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 0, 12)));
                    }
                }
                break;
            }
            case CoordinateTypes.UTM:
            {
                // Hemisphere  // Zone
                setZone_Hemi();
                zoneHemiPanel.setBounds(0, 0, 462, 55);
                if (state == ConversionState.INTERACTIVE)
                    hemiBoxPanel.setVisible(true);
                else
                    hemiBoxPanel.setVisible(false);

                zoneBoxPanel.setVisible(true);
                if (!Platform.isJavaV1_3)
                {
                    if (Platform.isUnix)
                    {
                        if (currLookAndFeel.equals("Java"))
                            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                               javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 10), java.awt.Color.black));
                        else
                            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                               javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 0, 10), java.awt.Color.black));
                    }
                    else
                    {
                        if (currLookAndFeel.equals("Java"))
                            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                                   javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 12)));
                        else
                            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                                   javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 0, 12)));
                    }
                }
                break;
            }
            case CoordinateTypes.LOCCART:
            {
                setLCFourParams();
                _3ParamFieldsRow1TextFieldC.setEditable(true);
                break;
            }
            case CoordinateTypes.OMERC:
            {
                setEightParams();
                break;
            }
            case CoordinateTypes.ALBERS:
            case CoordinateTypes.LAMBERT_2:
            {
                setSixParams();
                break;
            }
            case CoordinateTypes.NEYS:
            {
                setSixParams();
                _4ParamFieldsRow1Panel.setVisible(false);
                neysParamsRow1Panel.setVisible(true);
                neys71RadioButton.setSelected(true);
                try
                {
                    centralMeridianNeysParamsTextField.setText(jniStrtoval.JNILongitudeToString(0, useNSEW, useMinutes, useSeconds));
                    originLatitudeNeysParamsTextField.setText(jniStrtoval.JNILatitudeToString(80, useNSEW, useMinutes, useSeconds));
                    //2nd Std Parallel - set to read only at 89 59 58.0
                    stdParallel2NeysParamsTextField.setText(jniStrtoval.JNILatitudeToString(89.99944444444444, false, useMinutes, useSeconds));
                    //2nd Std Parallel - set to read only at 89 59 59.0
             ////       stdParallel2NeysParamsTextField.setText(jniStrtoval.JNILatitudeToString(89.99972222222222, false, useMinutes, useSeconds));
                }
                catch(GeotransError e)
                {
                    jniStrtoval.displayErrorMsg(this, e.getMessage());
                }
                catch(JNIException e)
                {
                    jniStrtoval.displayErrorMsg(this, e.getMessage());
                }

                if (!Platform.isJavaV1_3)
                {
                    if (Platform.isUnix)
                    {
                        if (currLookAndFeel.equals("Java"))
                            stdParallel1NeysParamsPanel.setBorder(new javax.swing.border.TitledBorder(null, "Std. Parallel 1:", javax.swing.border.TitledBorder.CENTER,
                                                      javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 10), java.awt.Color.black));
                        else
                            stdParallel1NeysParamsPanel.setBorder(new javax.swing.border.TitledBorder(null, "Std. Parallel 1:", javax.swing.border.TitledBorder.CENTER,
                                                      javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 0, 10), java.awt.Color.black));
                    }
                    else
                    {
                        if (currLookAndFeel.equals("Java"))
                            stdParallel1NeysParamsPanel.setBorder(new javax.swing.border.TitledBorder(null, "Std. Parallel 1:", javax.swing.border.TitledBorder.CENTER,
                                                    javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 12)));
                        else
                            stdParallel1NeysParamsPanel.setBorder(new javax.swing.border.TitledBorder(null, "Std. Parallel 1:", javax.swing.border.TitledBorder.CENTER,
                                                    javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 0, 12)));
                    }
                }
                break;
            }
            case CoordinateTypes.AZIMUTHAL:
            case CoordinateTypes.CASSINI:
            case CoordinateTypes.CYLEQA:
            case CoordinateTypes.GNOMONIC:
            case CoordinateTypes.ORTHOGRAPHIC:
            case CoordinateTypes.POLYCONIC:
            case CoordinateTypes.STEREOGRAPHIC:
            {
                setFourParams();
                break;
            }
            case CoordinateTypes.BONNE:
            {
                setFourParams();
                try
                {
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(45, useNSEW, useMinutes, useSeconds));
                }
                catch(GeotransError e)
                {
                    jniStrtoval.displayErrorMsg(this, e.getMessage());
                }
                catch(JNIException e)
                {
                    jniStrtoval.displayErrorMsg(this, e.getMessage());
                }
                break;
            }
            case CoordinateTypes.EQDCYL:
            {
                setFourParams();
                _4ParamFieldsRow1LabelC.setText("Standard Parallel:");
                break;
            }
            case CoordinateTypes.POLARSTEREO:
            {
                setFourParams();
                try
                {
                    _4ParamFieldsRow1LabelB.setText("Long. Down:");
                    _4ParamFieldsRow1LabelC.setText("Lat. of True Scale:");
                    _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(90, useNSEW, useMinutes, useSeconds));
                }
                catch(GeotransError e)
                {
                    jniStrtoval.displayErrorMsg(this, e.getMessage());
                }
                catch(JNIException e)
                {
                    jniStrtoval.displayErrorMsg(this, e.getMessage());
                }
                break;
            }
            case CoordinateTypes.ECKERT4:
            case CoordinateTypes.ECKERT6:
            case CoordinateTypes.MILLER:
            case CoordinateTypes.MOLLWEIDE:
            case CoordinateTypes.SINUSOIDAL:
            case CoordinateTypes.GRINTEN:
            {
                setThreeParams();
                break;
            }
            case CoordinateTypes.MERCATOR:
            {
                setFiveParams();
                _3ParamFieldsRow1LabelB.setText("Lat. of True Scale:");
                _3ParamFieldsRow1TextFieldC.setEditable(false);
                break;
            }
            case CoordinateTypes.LAMBERT_1:
            {
                setFiveParams();
                _3ParamFieldsRow1TextFieldC.setEditable(true);
                try
                {
                    _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(45, useNSEW, useMinutes, useSeconds));
                }
                catch(GeotransError e)
                {
                    jniStrtoval.displayErrorMsg(this, e.getMessage());
                }
                catch(JNIException e)
                {
                    jniStrtoval.displayErrorMsg(this, e.getMessage());
                }
                break;
            }
            case CoordinateTypes.TRCYLEQA:
            case CoordinateTypes.TRANMERC:
            {
                setFiveParams();
                _3ParamFieldsRow1TextFieldC.setEditable(true);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    // Set parameters & coordinates in geotrans engine
    public void setEngine()
    {
        try
        {
            jniEngine.JNISetDatum(state, direction, datumComboBox.getSelectedIndex());
            if (projectionType == CoordinateTypes.F16GRS)
                jniEngine.JNISetCoordinateSystem(state, direction, CoordinateTypes.MGRS);
            else
                jniEngine.JNISetCoordinateSystem(state, direction, projectionType);

            switch(projectionType)
            {
                case CoordinateTypes.ALBERS:
                {
                    AlbersEqualAreaConic albersParams = new AlbersEqualAreaConic(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Origin Latitude"),
                                                                                 jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Central Meridian"),
                                                                                 jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid 1st Standard Parallel"),
                                                                                 jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldD.getText().trim(), "Invalid 2nd Standard Parallel"),
                                                                                 jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                                 jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetAlbersEqualAreaConicParams(state, direction, albersParams);

                    break;
                }
                case CoordinateTypes.AZIMUTHAL:
                {
                    AzimuthalEquidistant azeqParams = new AzimuthalEquidistant(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Latitude"),
                                                                               jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                                               jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                               jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetAzimuthalEquidistantParams(state, direction, azeqParams);

                    break;
                }
                case CoordinateTypes.BONNE:
                {
                    Bonne bonneParams = new Bonne(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Latitude"),
                                                  jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                  jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                  jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetBonneParams(state, direction, bonneParams);

                    break;
                }
                case CoordinateTypes.CASSINI:
                {
                    Cassini cassiniParams = new Cassini(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Latitude"),
                                                        jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                        jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                        jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                   jniEngine.JNISetCassiniParams(state, direction, cassiniParams);

                    break;
                }
                case CoordinateTypes.CYLEQA:
                {
                    CylindricalEqualArea cyleqaParams = new CylindricalEqualArea(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Latitude"),
                                                                                 jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                                                 jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                                 jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetCylindricalEqualAreaParams(state, direction, cyleqaParams);

                    break;
                }
                case CoordinateTypes.ECKERT4:
                {
                    Eckert4 eckert4Params = new Eckert4(jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                        jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                        jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetEckert4Params(state, direction, eckert4Params);

                    break;
                }
                case CoordinateTypes.ECKERT6:
                {
                    Eckert6 eckert6Params = new Eckert6(jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                        jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                        jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetEckert6Params(state, direction, eckert6Params);

                    break;
                }
                case CoordinateTypes.EQDCYL:
                {
                    EquidistantCylindrical eqdcylParams = new EquidistantCylindrical(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Standard Parallel"),
                                                                                     jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                                                     jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                                     jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetEquidistantCylindricalParams(state, direction, eqdcylParams);

                    break;
                }
                case CoordinateTypes.GEODETIC:
                {
                    Geodetic geodeticParams = new Geodetic(heightType);

                    jniEngine.JNISetGeodeticParams(state, direction, geodeticParams);

                    break;
                }
                case CoordinateTypes.GNOMONIC:
                {
                    Gnomonic gnomonicParams = new Gnomonic(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Latitude"),
                                                           jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                           jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                           jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetGnomonicParams(state, direction, gnomonicParams);

                    break;
                }
                case CoordinateTypes.LAMBERT_1:
                {
                    LambertConformalConic1 lambert1Params = new LambertConformalConic1(jniStrtoval.stringToLatitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Origin Latitude"),
                                                                                                       jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Central Meridian"),
                                                                                                       jniStrtoval.stringToDouble(_3ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Scale Factor"),
                                                                                                       jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                                                       jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetLambertConformalConic1Params(state, direction, lambert1Params);

                    break;
                }
                case CoordinateTypes.LAMBERT_2:
                {
                    LambertConformalConic2 lambert2Params = new LambertConformalConic2(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Origin Latitude"),
                                                                                       jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Central Meridian"),
                                                                                       jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid 1st Standard Parallel"),
                                                                                       jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldD.getText().trim(), "Invalid 2nd Standard Parallel"),
                                                                                       jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                                       jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                     jniEngine.JNISetLambertConformalConic2Params(state, direction, lambert2Params);

                    break;
                }
                case CoordinateTypes.LOCCART:
                {
                    LocalCartesian loccartParams = new LocalCartesian(jniStrtoval.stringToLatitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Origin Latitude"),
                                                                      jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Origin Longitude"),
                                                                      jniStrtoval.stringToDouble(_3ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Height"),
                                                                      jniStrtoval.stringToLongitude(_3ParamFieldsRow2TextFieldB.getText().trim(), "Invalid Orientation"));
                    jniEngine.JNISetLocalCartesianParams(state, direction, loccartParams);

                    break;
                }
                case CoordinateTypes.MERCATOR:
                {
                    Mercator mercatorParams = new Mercator(jniStrtoval.stringToLatitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Latitude of True Scale"),
                                                           jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Central Meridian"),
                                                           jniStrtoval.stringToDouble(_3ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Scale Factor"),
                                                           jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                           jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetMercatorParams(state, direction, mercatorParams);

                    break;
                }
                case CoordinateTypes.MILLER:
                {
                    MillerCylindrical millerParams = new MillerCylindrical(jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                                           jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                           jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetMillerCylindricalParams(state, direction, millerParams);

                    break;
                }
                case CoordinateTypes.MOLLWEIDE:
                {
                    Mollweide mollweidParams = new Mollweide(jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                             jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                             jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetMollweideParams(state, direction, mollweidParams);

                    break;
                }
                case CoordinateTypes.NEYS:
                {
                    int std_par_1 = 71;

                    if (neys71RadioButton.isSelected() == true)
                      std_par_1 = 71;
                    else if (neys74RadioButton.isSelected() == true)
                      std_par_1 = 74;

                    Neys neysParams = new Neys(jniStrtoval.stringToLatitude(originLatitudeNeysParamsTextField.getText().trim(), "Invalid Origin Latitude"),
                                               jniStrtoval.stringToLongitude(centralMeridianNeysParamsTextField.getText().trim(), "Invalid Central Meridian"),
                                               std_par_1*jniStrtoval.PI/180,
                                               jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                               jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetNeysParams(state, direction, neysParams);

                    break;
                }
                case CoordinateTypes.OMERC:
                {
                    ObliqueMercator omercParams = new ObliqueMercator(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Origin Latitude"),
                                                                      jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldD.getText().trim(), "Invalid Latitude 1"),
                                                                      jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Longitude 1"),
                                                                      jniStrtoval.stringToLatitude(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid Latitude 2"),
                                                                      jniStrtoval.stringToLongitude(_4ParamFieldsRow2TextFieldA.getText().trim(), "Invalid Longitude 2"),
                                                                      jniStrtoval.stringToDouble(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Scale Factor"),
                                                                      jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Easting"),
                                                                      jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldD.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetObliqueMercatorParams(state, direction, omercParams);

                    break;
                }
                case CoordinateTypes.ORTHOGRAPHIC:
                {
                    Orthographic orthogrParams = new Orthographic(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Latitude"),
                                                                  jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                                  jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                  jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetOrthographicParams(state, direction, orthogrParams);

                    break;
                }
                case CoordinateTypes.POLARSTEREO:
                {
                    PolarStereographic polarstParams = new PolarStereographic(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid latitude of true scale"),
                                                                              jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid longitude down from pole"),
                                                                              jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                              jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetPolarStereographicParams(state, direction, polarstParams);

                    break;
                }
                case CoordinateTypes.POLYCONIC:
                {
                    Polyconic polyconParams = new Polyconic(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Latitude"),
                                                            jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                            jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                            jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetPolyconicParams(state, direction, polyconParams);

                    break;
                }
                case CoordinateTypes.SINUSOIDAL:
                {
                    Sinusoidal sinusoidParams = new Sinusoidal(jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                               jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                               jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetSinusoidalParams(state, direction, sinusoidParams);

                    break;
                }
                case CoordinateTypes.STEREOGRAPHIC:
                {
                    Stereographic stereogrParams = new Stereographic(jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Latitude"),
                                                                     jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                                     jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                     jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetStereographicParams(state, direction, stereogrParams);

                    break;
                }
                case CoordinateTypes.TRCYLEQA:
                {
                    TransverseCylindricalEqualArea trcyleqaParams = new TransverseCylindricalEqualArea(jniStrtoval.stringToLatitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Origin Latitude"),
                                                                                                       jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Central Meridian"),
                                                                                                       jniStrtoval.stringToDouble(_3ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Scale Factor"),
                                                                                                       jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                                                       jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetTransverseCylindricalEqualAreaParams(state, direction, trcyleqaParams);

                    break;
                }
                case CoordinateTypes.TRANMERC:
                {
                    TransverseMercator tranmercParams = new TransverseMercator(jniStrtoval.stringToLatitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Origin Latitude"),
                                                                               jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Central Meridian"),
                                                                               jniStrtoval.stringToDouble(_3ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Scale Factor"),
                                                                               jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                               jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetTransverseMercatorParams(state, direction, tranmercParams);

                    break;
                }
                case CoordinateTypes.GRINTEN:
                {
                    VanDerGrinten grintenParams = new VanDerGrinten(jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian"),
                                                                    jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting"),
                                                                    jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing"));
                    jniEngine.JNISetVanDerGrintenParams(state, direction, grintenParams);

                    break;
                }
                case CoordinateTypes.UTM:
                {
                    UTM UTMParams;
                    if(zoneRadioButton.isSelected())
                    {
                        long zone = jniStrtoval.stringToLong(zoneTextField.getText().trim(), "Invalid zone");
                        if ((zone < 1) || (zone > 60))
                            throw new GeotransError("Zone out of range (1-60)");
                        else
                            UTMParams = new UTM(jniStrtoval.stringToLong(zoneTextField.getText().trim(), "Invalid zone"), override);
                    }
                    else
                        UTMParams = new UTM(0, override);

                    jniEngine.JNISetUTMParams(state, direction, UTMParams);

                    break;
                }
                default:
                    break;
            }

            if ((state != ConversionState.FILE) && (direction != SourceOrTarget.TARGET))
            {
                if (projectionType == CoordinateTypes.UTM)
                {
                    coordPanel.setZone((int)jniStrtoval.stringToLong(zoneTextField.getText().trim(), "Invalid zone"));
                    if (nHemiRadioButton.isSelected())
                        coordPanel.setHemisphere('N');
                    else
                        coordPanel.setHemisphere('S');
                }
                else if (projectionType == CoordinateTypes.UPS)
                {
                    if (nHemiRadioButton.isSelected())
                        coordPanel.setHemisphere('N');
                    else
                        coordPanel.setHemisphere('S');
                }

                coordPanel.setCoords(state, direction, projectionType);
                coordPanel.setAccuracy();
            }
        }
        catch(GeotransError e)
        {
            jniStrtoval.setEngineError(true, e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.setJNIError(true, e.getMessage());
        }
    }


    private void createButtonGroups()
    {
        javax.swing.ButtonGroup hemi_group = new javax.swing.ButtonGroup();
        javax.swing.ButtonGroup neys_group = new javax.swing.ButtonGroup();

        hemi_group.add(nHemiRadioButton);
        hemi_group.add(sHemiRadioButton);

        neys_group.add(neys71RadioButton);
        neys_group.add(neys74RadioButton);
    }

    private void hideParams()
    {
        paramFieldsRow1LayeredPane.setMinimumSize(new java.awt.Dimension(460, 55));
        paramFieldsRow1LayeredPane.setMaximumSize(new java.awt.Dimension(460, 55));
        paramFieldsRow1LayeredPane.setPreferredSize(new java.awt.Dimension(460, 55));

        paramFieldsRow2LayeredPane.setMinimumSize(new java.awt.Dimension(460, 55));
        paramFieldsRow2LayeredPane.setMaximumSize(new java.awt.Dimension(460, 55));
        paramFieldsRow2LayeredPane.setPreferredSize(new java.awt.Dimension(460, 55));

        _3ParamFieldsRow1Panel.setBounds(0, 0, 462, 38);
        _3ParamFieldsRow2Panel.setBounds(0, 0, 462, 38);

        _3ParamFieldsRow1Panel.setVisible(false);
        _4ParamFieldsRow1Panel.setVisible(false);
        _3ParamFieldsRow2Panel.setVisible(false);
        _4ParamFieldsRow2Panel.setVisible(false);
        neysParamsRow1Panel.setVisible(false);
        zoneHemiPanel.setVisible(false);
        heightPanel.setVisible(false);
        heightLabelPanel.setVisible(false);
    }

    private void setHeight()
    {
        hideParams();
        heightPanel.setVisible(true);
        paramFieldsRow2LayeredPane.moveToFront(heightPanel);
        try
        {
            int inputFileType = jniEngine.JNIGetCoordinateSystem(state, SourceOrTarget.SOURCE);
            if ((state == ConversionState.FILE) && (!createHeader) &&
                ((inputFileType != CoordinateTypes.GEODETIC) && (inputFileType != CoordinateTypes.GEOCENTRIC) && (inputFileType != CoordinateTypes.LOCCART)))
                selectNoHeightButton();
            else
            {
                heightType = HeightType.ELLIPSOID_HEIGHT;
                heightComboBox.setSelectedIndex(heightType);
           }
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
    }

     private void setZone_Hemi()
    {
        hideParams();
        zoneHemiPanel.setVisible(true);
        paramFieldsRow2LayeredPane.moveToFront(zoneHemiPanel);
        /* initialize hemisphere*/
        nHemiRadioButton.setSelected(true);
        /* initialize zone override*/
        zoneTextField.setText( "0" );
        zoneRadioButton.setSelected(false);
        override = 0;
    }

    private void setThreeParams()
    {
        setFormat();
        hideParams();
        _3ParamFieldsRow1Panel.setVisible(true);
        _4ParamFieldsRow2Panel.setVisible(true);

        paramFieldsRow1LayeredPane.setMinimumSize(new java.awt.Dimension(439, 55));
        paramFieldsRow1LayeredPane.setMaximumSize(new java.awt.Dimension(439, 55));
        paramFieldsRow1LayeredPane.setPreferredSize(new java.awt.Dimension(439, 55));

        _3ParamFieldsRow1Panel.setBounds(2, 2, 439, 37);

           // Hide Extra Fields
        _3ParamFieldsRow1LabelA.setVisible(false);
        _3ParamFieldsRow1LabelC.setVisible(false);
        _4ParamFieldsRow2LabelA.setVisible(false);
        _4ParamFieldsRow2LabelD.setVisible(false);
        _3ParamFieldsRow1TextFieldA.setVisible(false);
        _3ParamFieldsRow1TextFieldC.setVisible(false);
        _4ParamFieldsRow2TextFieldA.setVisible(false);
        _4ParamFieldsRow2TextFieldD.setVisible(false);

        _3ParamFieldsRow1LabelB.setText("Central Meridian:");
        _4ParamFieldsRow2LabelB.setText("False Easting (m):");
        _4ParamFieldsRow2LabelC.setText("False Northing (m):");
        try
        {
            _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(0, useNSEW, useMinutes, useSeconds));
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        _4ParamFieldsRow2TextFieldB.setText( "0" );
        _4ParamFieldsRow2TextFieldC.setText( "0" );
    } // end setThreeParams()

    private void setThreeParamsUnedit()
    {
        _3ParamFieldsRow1TextFieldB.setEditable(false);
        _4ParamFieldsRow2TextFieldB.setEditable(false);
        _4ParamFieldsRow2TextFieldC.setEditable(false);
    }

    private void setFourParams()
    {
        setFormat();
        hideParams();
        _4ParamFieldsRow1Panel.setVisible(true);
        _4ParamFieldsRow2Panel.setVisible(true);

        // Hide Extra Fields
        _4ParamFieldsRow1LabelA.setVisible(false);
        _4ParamFieldsRow1LabelD.setVisible(false);
        _4ParamFieldsRow2LabelA.setVisible(false);
        _4ParamFieldsRow2LabelD.setVisible(false);
        _4ParamFieldsRow1TextFieldA.setVisible(false);
        _4ParamFieldsRow1TextFieldD.setVisible(false);
        _4ParamFieldsRow2TextFieldA.setVisible(false);
        _4ParamFieldsRow2TextFieldD.setVisible(false);

        _4ParamFieldsRow1LabelB.setText("Central Meridian:");
        _4ParamFieldsRow1LabelC.setText("Origin Latitude:");
        _4ParamFieldsRow2LabelB.setText("False Easting (m):");
        _4ParamFieldsRow2LabelC.setText("False Northing (m):");
        try
        {
            _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(0, useNSEW, useMinutes, useSeconds));
            _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(0, useNSEW, useMinutes, useSeconds));
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        _4ParamFieldsRow2TextFieldB.setText( "0" );
        _4ParamFieldsRow2TextFieldC.setText( "0" );
    }  // end setFourParams()

    private void setFourParamsUnedit()
    {
        _4ParamFieldsRow1TextFieldB.setEditable(false);
        _4ParamFieldsRow1TextFieldC.setEditable(false);
        _4ParamFieldsRow2TextFieldB.setEditable(false);
        _4ParamFieldsRow2TextFieldC.setEditable(false);
    }

    private void setLCFourParams()
    {
        setFormat();
        hideParams();
        _3ParamFieldsRow1Panel.setVisible(true);
        _3ParamFieldsRow2Panel.setVisible(true);

        paramFieldsRow1LayeredPane.setMinimumSize(new java.awt.Dimension(439, 55));
        paramFieldsRow1LayeredPane.setMaximumSize(new java.awt.Dimension(439, 55));
        paramFieldsRow1LayeredPane.setPreferredSize(new java.awt.Dimension(439, 55));

        paramFieldsRow2LayeredPane.setMinimumSize(new java.awt.Dimension(439, 55));
        paramFieldsRow2LayeredPane.setMaximumSize(new java.awt.Dimension(439, 55));
        paramFieldsRow2LayeredPane.setPreferredSize(new java.awt.Dimension(439, 55));

        _3ParamFieldsRow1Panel.setBounds(2, 2, 439, 37);
        _3ParamFieldsRow2Panel.setBounds(2, 2, 439, 37);

           // Show Extra Fields
        _3ParamFieldsRow1LabelA.setVisible(true);
        _3ParamFieldsRow1LabelC.setVisible(true);
        _3ParamFieldsRow1TextFieldA.setVisible(true);
        _3ParamFieldsRow1TextFieldC.setVisible(true);
        // Hide Extra Fields
        _3ParamFieldsRow2LabelA.setVisible(false);
        _3ParamFieldsRow2LabelC.setVisible(false);
        _3ParamFieldsRow2TextFieldA.setVisible(false);
        _3ParamFieldsRow2TextFieldC.setVisible(false);

        _3ParamFieldsRow1LabelA.setText("Origin Longitude:");
        _3ParamFieldsRow1LabelB.setText("Origin Latitude:");
        _3ParamFieldsRow1LabelC.setText("Origin Height (m):");
        _3ParamFieldsRow2LabelB.setText("Orientation:");
        try
        {
            _3ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(0, useNSEW, useMinutes, useSeconds));
            _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(0, useNSEW, useMinutes, useSeconds));
            _3ParamFieldsRow1TextFieldC.setText( "0" );
            _3ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNILongitudeToString(0, useNSEW, useMinutes, useSeconds));
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
    }

    private void setLCFourParamsUnedit()
    {
        _3ParamFieldsRow1TextFieldA.setEditable(false);
        _3ParamFieldsRow1TextFieldB.setEditable(false);
        _3ParamFieldsRow1TextFieldC.setEditable(false);
        _3ParamFieldsRow2TextFieldB.setEditable(false);
    }

    private void setFiveParams()
    {
        setFormat();
        hideParams();
        _3ParamFieldsRow1Panel.setVisible(true);
        _4ParamFieldsRow2Panel.setVisible(true);

        paramFieldsRow1LayeredPane.setMinimumSize(new java.awt.Dimension(439, 55));
        paramFieldsRow1LayeredPane.setMaximumSize(new java.awt.Dimension(439, 55));
        paramFieldsRow1LayeredPane.setPreferredSize(new java.awt.Dimension(439, 55));

        _3ParamFieldsRow1Panel.setBounds(2, 2, 439, 37);

           // Show Extra Fields
        _3ParamFieldsRow1LabelA.setVisible(true);
        _3ParamFieldsRow1LabelC.setVisible(true);
        _3ParamFieldsRow1TextFieldA.setVisible(true);
        _3ParamFieldsRow1TextFieldC.setVisible(true);

        // Hide Extra Fields
        _4ParamFieldsRow2LabelA.setVisible(false);
        _4ParamFieldsRow2LabelD.setVisible(false);
        _4ParamFieldsRow2TextFieldA.setVisible(false);
        _4ParamFieldsRow2TextFieldD.setVisible(false);

        _3ParamFieldsRow1LabelA.setText("Central Meridian:");
        _3ParamFieldsRow1LabelB.setText("Origin Latitude:");
        _3ParamFieldsRow1LabelC.setText("Scale Factor:");
        _4ParamFieldsRow2LabelB.setText("False Easting (m):");
        _4ParamFieldsRow2LabelC.setText("False Northing (m):");
        try
        {
            _3ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(0, useNSEW, useMinutes, useSeconds));
            _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(0, useNSEW, useMinutes, useSeconds));
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        _3ParamFieldsRow1TextFieldC.setText( "1.00000" );
        _4ParamFieldsRow2TextFieldB.setText( "0" );
        _4ParamFieldsRow2TextFieldC.setText( "0" );
    } // end setFiveParams()

    private void setFiveParamsUnedit()
    {
        _3ParamFieldsRow1TextFieldA.setEditable(false);
        _3ParamFieldsRow1TextFieldB.setEditable(false);
        _3ParamFieldsRow1TextFieldC.setEditable(false);
        _4ParamFieldsRow2TextFieldB.setEditable(false);
        _4ParamFieldsRow2TextFieldC.setEditable(false);
    }

    private void setSixParams()
    {
        setFormat();
        hideParams();
        _4ParamFieldsRow1Panel.setVisible(true);
        _4ParamFieldsRow2Panel.setVisible(true);

        // Show/Hide Extra Fields
        _4ParamFieldsRow1LabelA.setVisible(true);
        _4ParamFieldsRow1LabelD.setVisible(true);
        _4ParamFieldsRow2LabelA.setVisible(false);
        _4ParamFieldsRow2LabelD.setVisible(false);
        _4ParamFieldsRow1TextFieldA.setVisible(true);
        _4ParamFieldsRow1TextFieldD.setVisible(true);
        _4ParamFieldsRow2TextFieldA.setVisible(false);
        _4ParamFieldsRow2TextFieldD.setVisible(false);

        _4ParamFieldsRow1LabelA.setText("Central Meridian:");
        _4ParamFieldsRow1LabelB.setText("Origin Latitude:");
        _4ParamFieldsRow1LabelC.setText("Std. Parallel 1:");
        _4ParamFieldsRow1LabelD.setText("Std. Parallel 2:");
        _4ParamFieldsRow2LabelB.setText("False Easting (m):");
        _4ParamFieldsRow2LabelC.setText("False Northing (m):");
        try
        {
            _4ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(0, useNSEW, useMinutes, useSeconds));
            _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(45, useNSEW, useMinutes, useSeconds));
            _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(40, useNSEW, useMinutes, useSeconds));
            _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(50, useNSEW, useMinutes, useSeconds));
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        _4ParamFieldsRow2TextFieldB.setText( "0" );
        _4ParamFieldsRow2TextFieldC.setText( "0" );
    } // end setSixParams()

    private void setSixParamsUnedit()
    {
        _4ParamFieldsRow1TextFieldA.setEditable(false);
        _4ParamFieldsRow1TextFieldB.setEditable(false);
        _4ParamFieldsRow1TextFieldC.setEditable(false);
        _4ParamFieldsRow1TextFieldD.setEditable(false);
        _4ParamFieldsRow2TextFieldB.setEditable(false);
        _4ParamFieldsRow2TextFieldC.setEditable(false);
    }

    private void setEightParams()
    {
        setFormat();
        hideParams();
        _4ParamFieldsRow1Panel.setVisible(true);
        _4ParamFieldsRow2Panel.setVisible(true);

        // Show/Hide Extra Fields
        _4ParamFieldsRow1LabelA.setVisible(true);
        _4ParamFieldsRow1LabelD.setVisible(true);
        _4ParamFieldsRow2LabelA.setVisible(true);
        _4ParamFieldsRow2LabelD.setVisible(true);
        _4ParamFieldsRow1TextFieldA.setVisible(true);
        _4ParamFieldsRow1TextFieldD.setVisible(true);
        _4ParamFieldsRow2TextFieldA.setVisible(true);
        _4ParamFieldsRow2TextFieldD.setVisible(true);

        _4ParamFieldsRow1LabelA.setText("Origin Latitude:");
        _4ParamFieldsRow1LabelB.setText("Scale Factor:");
        _4ParamFieldsRow1LabelC.setText("Longitude 1:");
        _4ParamFieldsRow1LabelD.setText("Latitude 1:");
        _4ParamFieldsRow2LabelA.setText("Longitude 2:");
        _4ParamFieldsRow2LabelB.setText("Latitude 2:");
        _4ParamFieldsRow2LabelC.setText("False Easting (m):");
        _4ParamFieldsRow2LabelD.setText("False Northing (m):");
        try
        {
            _4ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILatitudeToString(45, useNSEW, useMinutes, useSeconds));
            _4ParamFieldsRow1TextFieldB.setText("1.00000");
            _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILongitudeToString(-5, useNSEW, useMinutes, useSeconds));
            _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(40, useNSEW, useMinutes, useSeconds));
            _4ParamFieldsRow2TextFieldA.setText(jniStrtoval.JNILongitudeToString(5, useNSEW, useMinutes, useSeconds));
            _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNILatitudeToString(50, useNSEW, useMinutes, useSeconds));
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.displayErrorMsg(this, e.getMessage());
        }
        _4ParamFieldsRow2TextFieldC.setText("0");
        _4ParamFieldsRow2TextFieldD.setText("0");
    } // end setEightParams()

    private void setEightParamsUnedit()
    {
        _4ParamFieldsRow1TextFieldA.setEditable(false);
        _4ParamFieldsRow1TextFieldB.setEditable(false);
        _4ParamFieldsRow1TextFieldC.setEditable(false);
        _4ParamFieldsRow1TextFieldD.setEditable(false);
        _4ParamFieldsRow2TextFieldA.setEditable(false);
        _4ParamFieldsRow2TextFieldB.setEditable(false);
        _4ParamFieldsRow2TextFieldC.setEditable(false);
        _4ParamFieldsRow2TextFieldD.setEditable(false);
    }

    private void fillHeightList()
    {
         heightComboBox.addItem("No Height");
         heightComboBox.addItem("Ellipsoid Height");
         heightComboBox.addItem("MSL-EGM96-15M-BL Height (recommended)");
         heightComboBox.addItem("MSL-EGM96-VG-NS Height");
         heightComboBox.addItem("MSL-EGM84-10D-BL Height");
         heightComboBox.addItem("MSL-EGM84-10D-NS Height");
   }



    // Fill the projection combo box
    private void fillProjectionList()
    {
        projectionComboBox.addItem("Geodetic");
        projectionComboBox.addItem("GEOREF");
        projectionComboBox.addItem("Global Area Reference System (GARS)");
        projectionComboBox.addItem("Geocentric");
        projectionComboBox.addItem("Local Cartesian");
        projectionComboBox.addItem("Military Grid Reference System (MGRS)");
        projectionComboBox.addItem("United States National Grid (USNG)");
        projectionComboBox.addItem("Universal Transverse Mercator (UTM)");
        projectionComboBox.addItem("Universal Polar Stereographic (UPS)");
        projectionComboBox.addItem("Albers Equal Area Conic");
        projectionComboBox.addItem("Azimuthal Equidistant (S)");
        projectionComboBox.addItem("British National Grid");
        projectionComboBox.addItem("Bonne");
        projectionComboBox.addItem("Cassini");
        projectionComboBox.addItem("Cylindrical Equal Area");
        projectionComboBox.addItem("Eckert IV (S)");
        projectionComboBox.addItem("Eckert VI (S)");
        projectionComboBox.addItem("Equidistant Cylindrical (S)");
        projectionComboBox.addItem("Gnomonic (S)");
        projectionComboBox.addItem("Lambert Conformal Conic (1 parallel)");
        projectionComboBox.addItem("Lambert Conformal Conic (2 parallel)");
        projectionComboBox.addItem("Mercator");
        projectionComboBox.addItem("Miller Cylindrical (S)");
        projectionComboBox.addItem("Mollweide (S)");
        projectionComboBox.addItem("Ney's (Modified Lambert Conformal Conic)");
        projectionComboBox.addItem("New Zealand Map Grid");
        projectionComboBox.addItem("Oblique Mercator");
        projectionComboBox.addItem("Orthographic (S)");
        projectionComboBox.addItem("Polar Stereographic");
        projectionComboBox.addItem("Polyconic");
        projectionComboBox.addItem("Sinusoidal");
        projectionComboBox.addItem("Stereographic (S)");
        projectionComboBox.addItem("Transverse Cylindrical Equal Area");
        projectionComboBox.addItem("Transverse Mercator");
        projectionComboBox.addItem("Van der Grinten");
        if (state != ConversionState.FILE)
            projectionComboBox.addItem("F-16 Grid Reference System");
        projectionComboBox.updateUI();
    }


    private void setFormat()
    {
        useNSEW = formatOptions.getUseNSEW();
        useMinutes = formatOptions.getUseMinutes();
        useSeconds = formatOptions.getUseSeconds();
    }


/**
    * @param args the command line arguments
    */
    public static void main (String args[]) {
   //     jOptions joptions = new jOptions();
   //     JNIFiomeths jniFiomeths = new JNIFiomeths();
   //     new FileDlg (new javax.swing.JFrame (), true, null, joptions, jniFiomeths).show ();
    }



    // Add new datum to combo box
    public void addDatumToList()
    {
      int currentListIndex = datumIndex - 1;
      datumList = new FillList(datumComboBox, ListType.DATUM);
      datumComboBox.setSelectedIndex(currentListIndex);
      ///  datumList.addDatum(datumComboBox);
    }

    // Remove datum from combo box
    public void deleteDatumFromList(int index)
    {
      int currentListIndex = datumIndex - 1;
      datumList = new FillList(datumComboBox, ListType.DATUM);
      datumComboBox.setSelectedIndex(currentListIndex);
    ////     datumList.deleteDatum(datumComboBox, index);
    }

    public void getCoords(int dir)
    {
        if(coordPanel.getCoords(state, dir, projectionType))
        {
            if (projectionType == CoordinateTypes.MERCATOR)
            {
                try
                {
                    Mercator mercatorParams = jniEngine.JNIGetMercatorParams(state, dir);
                    jniStrtoval.setNumberFormat(_3ParamFieldsRow1TextFieldC, mercatorParams.getScaleFactor(), 5);

                }
                catch(GeotransError e)
                {
                    jniStrtoval.displayErrorMsg(this, e.getMessage());
                }
                catch(JNIException e)
                {
                    jniStrtoval.displayErrorMsg(this, e.getMessage());
                }
            }
            else if (projectionType == CoordinateTypes.UTM)
            {
                zoneTextField.setText(String.valueOf(coordPanel.getZone()));
                if (coordPanel.getHemisphere() == 'N')
                    nHemiRadioButton.setSelected(true);
                else
                    sHemiRadioButton.setSelected(true);
            }
            else if (projectionType == CoordinateTypes.UPS)
            {
                if (coordPanel.getHemisphere() == 'N')
                    nHemiRadioButton.setSelected(true);
                else
                    sHemiRadioButton.setSelected(true);
            }
        }
    }

    public void showErrors(java.awt.Component parent)
    {
        jniStrtoval.displayErrorMsg(parent, direction, projectionType);
    }

    public boolean engineError()
    {
        return jniStrtoval.getEngineError();
    }

    public boolean JNIError()
    {
        return jniStrtoval.getJNIError();
    }

    public void setHeightFieldEditable(boolean editable)
    {
        coordPanel.setHeightFieldEditable(editable);
    }

    public void setHeightText(String height)
    {
        coordPanel.setHeightText(height);
    }

    public void selectNoHeightButton()
    {
        heightType = HeightType.NO_HEIGHT;
        heightComboBox.setSelectedIndex(heightType);
    }

    public void selectEllipsoidHeightButton()
    {
        heightType = HeightType.ELLIPSOID_HEIGHT;
        heightComboBox.setSelectedIndex(heightType);
    }

    public void enableHeightComboBox(boolean enable)
    {
        heightComboBox.setEnabled(enable);
    }

    public int getProjectionType()
    {
        return projectionType;
    }

    public String getProjectionCode()
    {
      try
      {
        return jniEngine.JNIGetCoordinateSystemCode(projectionType + 1);
      }
      catch(Exception e)
      {
        jniStrtoval.displayErrorMsg(this, e.getMessage());
        return "";
      }
    }

    public int getDatumIndex()
    {
        return datumIndex;
    }

    public String getDatumCode()
    {
      try
      {
        return jniEngine.JNIGetDatumCode(datumIndex);
      }
      catch(Exception e)
      {
        jniStrtoval.displayErrorMsg(this, e.getMessage());
        return "";
      }
    }

    public void reportAccuracy()
    {
        coordPanel.reportOutputErrors(state);
    }

    public void resetAccuracy()
    {
        coordPanel.resetOutputErrors();
    }

    public void updateSrcErrors(boolean _3dConversion)
    {
        coordPanel.updateSrcErrors(_3dConversion);
    }

    // Geotrans parent class
    public void setParent(Geotrans par)
    {
        parent = par;
    }
    public void setProjectionDir(int dir)
    {
        direction = dir;
    }

    public void setLookAndFeel(String lookAndFeel)
    {
        currLookAndFeel = lookAndFeel;
        if (!Platform.isJavaV1_3)
        {
            switch (projectionType)
            {
                case CoordinateTypes.UPS:
                case CoordinateTypes.UTM:
                {
                    if (Platform.isUnix)
                    {
                        if (currLookAndFeel.equals("Java"))
                            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                               javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 10), java.awt.Color.black));
                        else
                            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                               javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 0, 10), java.awt.Color.black));
                    }
                    else
                    {
                        if (currLookAndFeel.equals("Java"))
                            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                                   javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 12)));
                        else
                            hemiBoxPanel.setBorder(new javax.swing.border.TitledBorder(null, "Hemisphere:", javax.swing.border.TitledBorder.CENTER,
                                                   javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 0, 12)));
                    }
                    break;
                }
                case CoordinateTypes.NEYS:
                {
                    if (Platform.isUnix)
                    {
                        if (currLookAndFeel.equals("Java"))
                            stdParallel1NeysParamsPanel.setBorder(new javax.swing.border.TitledBorder(null, "Std. Parallel 1:", javax.swing.border.TitledBorder.CENTER,
                                                      javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 10), java.awt.Color.black));
                        else
                            stdParallel1NeysParamsPanel.setBorder(new javax.swing.border.TitledBorder(null, "Std. Parallel 1:", javax.swing.border.TitledBorder.CENTER,
                                                      javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 0, 10), java.awt.Color.black));
                    }
                    else
                    {
                        if (currLookAndFeel.equals("Java"))
                            stdParallel1NeysParamsPanel.setBorder(new javax.swing.border.TitledBorder(null, "Std. Parallel 1:", javax.swing.border.TitledBorder.CENTER,
                                                    javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 1, 12)));
                        else
                            stdParallel1NeysParamsPanel.setBorder(new javax.swing.border.TitledBorder(null, "Std. Parallel 1:", javax.swing.border.TitledBorder.CENTER,
                                                    javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Dialog", 0, 12)));
                    }
                }
        }
        }
    }

    
 // Get Parameters
    
  public int getGeodeticHeight()
  {
      return heightType;
  }
  
  
  public long getZone()
  {
    if(zoneRadioButton.isSelected())
    {
        long zone = jniStrtoval.stringToLong(zoneTextField.getText().trim(), "Invalid zone");
        if ((zone < 1) || (zone > 60))
            return 0;
        else
            return zone;
    }
    else
        return 0;
  }
  
  
  public long getOverride()
  {
    return override;
  }

  
  public double get3ParamCentralMeridian()
  {
    return jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian") * _180OverPI;
  }
  
  
  public double getFalseEasting()
  {
    return jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid False Easting");
  }
  
  
  public double getFalseNorthing()
  {
    return jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Northing");
  }
  
  
  public double get4ParamCentralMeridian()
  {
    return jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Central Meridian") * _180OverPI;
  }
  
  
  public double get4ParamOriginLatitude()
  {
    return jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Latitude") * _180OverPI;
  }
  
  
  public double get5ParamCentralMeridian()
  {
    return jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Central Meridian") * _180OverPI;
  }
  
  
  public double get5ParamOriginLatitude()
  {
    return jniStrtoval.stringToLatitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Origin Latitude") * _180OverPI;
  }
  
  
  public double get5ParamScaleFactor()
  {
    return Double.parseDouble(_3ParamFieldsRow1TextFieldC.getText().trim());
  }
  
  
  public double get6ParamCentralMeridian()
  {
    return jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Central Meridian") * _180OverPI;
  }
  
  
  public double get6ParamOriginLatitude()
  {
    return jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Origin Latitude") * _180OverPI;
  }
  
  
  public double get6ParamStandardParallel1()
  {
    return jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid 1st Standard Parallel") * _180OverPI;
  }
  
  
  public double get6ParamStandardParallel2()
  {
    return jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldD.getText().trim(), "Invalid 2nd Standard Parallel") * _180OverPI;
  }
  
  
  public double getOriginLongitude()
  {
    return jniStrtoval.stringToLongitude(_3ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Origin Longitude") * _180OverPI;
  }
  
  
  public double getOriginLatitude()
  {
    return jniStrtoval.stringToLatitude(_3ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Origin Latitude") * _180OverPI;
  }

  
  public double getOriginHeight()
  {
    return jniStrtoval.stringToDouble(_3ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Origin Height");
  }

  
  public double getOrientation()
  {
    return jniStrtoval.stringToLongitude(_3ParamFieldsRow2TextFieldB.getText().trim(), "Invalid Orientation") * _180OverPI;
  }
  
  
  public double getNeysCentralMeridian()
  {
    return jniStrtoval.stringToLongitude(centralMeridianNeysParamsTextField.getText().trim(), "Invalid Central Meridian") * _180OverPI;
  }
  
  
  public double getNeysOriginLatitude()
  {
    return jniStrtoval.stringToLatitude(originLatitudeNeysParamsTextField.getText().trim(), "Invalid Origin Latitude") * _180OverPI;
  }
  
  
  public double getNeysStandardParallel1()
  {
    double std_par_1 = 71.0;

    if (neys74RadioButton.isSelected() == true)
      std_par_1 = 74.0;
    
    return std_par_1;
  }

  
  public double getOmercOriginLatitude()
  {
    return jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldA.getText().trim(), "Invalid Origin Latitude") * _180OverPI;
  }

  
  public double getOmercLongitude1()
  {
    return jniStrtoval.stringToLongitude(_4ParamFieldsRow1TextFieldC.getText().trim(), "Invalid Longitude 1") * _180OverPI;
  }

  
  public double getOmercLatitude1()
  {
    return jniStrtoval.stringToLatitude(_4ParamFieldsRow1TextFieldD.getText().trim(), "Invalid Latitude 1") * _180OverPI;
  }

  
  public double getOmercLongitude2()
  {
    return jniStrtoval.stringToLongitude(_4ParamFieldsRow2TextFieldA.getText().trim(), "Invalid Longitude 2") * _180OverPI;
  }

  
  public double getOmercLatitude2()
  {
    return jniStrtoval.stringToLatitude(_4ParamFieldsRow2TextFieldB.getText().trim(), "Invalid Latitude 2") * _180OverPI;
  }

  
  public double getOmercFalseEasting()
  {
    return jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldC.getText().trim(), "Invalid False Easting");
  }

  
  public double getOmercFalseNorthing()
  {
    return jniStrtoval.stringToDouble(_4ParamFieldsRow2TextFieldD.getText().trim(), "Invalid False Northing");
  }

  
  public double getOmercScaleFactor()
  {
    return jniStrtoval.stringToDouble(_4ParamFieldsRow1TextFieldB.getText().trim(), "Invalid Scale Factor");
  }
  
  
  public void setDefaults(int _datumIndex, int _projectionType, CoordinateSystemParameters _parameters)
  {
    datumIndex = _datumIndex;
    projectionType = _projectionType;
    
    datumComboBox.setSelectedIndex(datumIndex);
    projectionComboBox.setSelectedItem(CoordinateTypes.name(projectionType));

    createMasterPanel();
    
    try
    {
      switch(projectionType)
      {
        case CoordinateTypes.ECKERT4:
        case CoordinateTypes.ECKERT6:
        case CoordinateTypes.MILLER:
        case CoordinateTypes.MOLLWEIDE:
        case CoordinateTypes.SINUSOIDAL:
        case CoordinateTypes.GRINTEN:
        {
          MapProjection3Parameters parameters = (MapProjection3Parameters)_parameters;
          _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(parameters.getCentralMeridian(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(parameters.getFalseEasting()));
          _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(parameters.getFalseNorthing()));
          break;
        }
        case CoordinateTypes.AZIMUTHAL:
        case CoordinateTypes.BONNE:
        case CoordinateTypes.CASSINI:
        case CoordinateTypes.CYLEQA:
        case CoordinateTypes.GNOMONIC:
        case CoordinateTypes.ORTHOGRAPHIC:
        case CoordinateTypes.POLYCONIC:
        case CoordinateTypes.STEREOGRAPHIC:
        {
          MapProjection4Parameters parameters = (MapProjection4Parameters)_parameters;
          _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(parameters.getCentralMeridian(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(parameters.getOriginLatitude(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(parameters.getFalseEasting()));
          _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(parameters.getFalseNorthing()));
          break;
        }
        case CoordinateTypes.EQDCYL:
        {
          EquidistantCylindricalParameters parameters = (EquidistantCylindricalParameters)_parameters;
          _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(parameters.getCentralMeridian(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(parameters.getStandardParallel(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(parameters.getFalseEasting()));
          _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(parameters.getFalseNorthing()));
          break;          
        }
        case CoordinateTypes.LAMBERT_1:
        case CoordinateTypes.TRCYLEQA:
        case CoordinateTypes.TRANMERC:
        {
          MapProjection5Parameters parameters = (MapProjection5Parameters)_parameters;
          _3ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(parameters.getCentralMeridian(), useNSEW, useMinutes, useSeconds));
          _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(parameters.getOriginLatitude(), useNSEW, useMinutes, useSeconds));

          jniStrtoval.setNumberFormat(_3ParamFieldsRow1TextFieldC, parameters.getScaleFactor(), 5);

          _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(parameters.getFalseEasting()));
          _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(parameters.getFalseNorthing()));
          break;
        }
        case CoordinateTypes.MERCATOR:
        {
          MercatorParameters parameters = (MercatorParameters)_parameters;
          _3ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(parameters.getCentralMeridian(), useNSEW, useMinutes, useSeconds));
          _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(parameters.getLatitudeOfTrueScale(), useNSEW, useMinutes, useSeconds));

          jniStrtoval.setNumberFormat(_3ParamFieldsRow1TextFieldC, parameters.getScaleFactor(), 5);

          _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(parameters.getFalseEasting()));
          _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(parameters.getFalseNorthing()));
          break;
        }
        case CoordinateTypes.ALBERS:
        case CoordinateTypes.LAMBERT_2:
        {
          MapProjection6Parameters parameters = (MapProjection6Parameters)_parameters;
          _4ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(parameters.getCentralMeridian(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(parameters.getOriginLatitude(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(parameters.getStandardParallel1(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(parameters.getStandardParallel2(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(parameters.getFalseEasting()));
          _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(parameters.getFalseNorthing()));
          break;
        }
        case CoordinateTypes.LOCCART:
        {
          LocalCartesianParameters parameters = (LocalCartesianParameters)_parameters;
          _3ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILongitudeToString(parameters.getLongitude(), useNSEW, useMinutes, useSeconds));
          _3ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILatitudeToString(parameters.getLatitude(), useNSEW, useMinutes, useSeconds));
          _3ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNIMeterToString(parameters.getHeight()));
          _3ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNILongitudeToString(parameters.getOrientation(), useNSEW, useMinutes, useSeconds));
          break;
        }
        case CoordinateTypes.NEYS:
        {
          NeysParameters parameters = (NeysParameters)_parameters;
          boolean northHemi = true;

          double olat = parameters.getOriginLatitude();
          if (olat < 0)
              northHemi = false;
          centralMeridianNeysParamsTextField.setText(jniStrtoval.JNILongitudeToString(parameters.getCentralMeridian(), useNSEW, useMinutes, useSeconds));
          originLatitudeNeysParamsTextField.setText(jniStrtoval.JNILatitudeToString(olat, useNSEW, useMinutes, useSeconds));
          
          double standardParallel1 = parameters.getStandardParallel1();
          if(standardParallel1 == 71.0)
          {
            neys71RadioButton.setSelected(true);
            neys74RadioButton.setSelected(false);
          }
          else
          {
            neys71RadioButton.setSelected(false);
            neys74RadioButton.setSelected(true);
          }
      //    if (northHemi)
      //        _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(parameters.getStandardParallel1(), useNSEW, useMinutes, useSeconds));
      //    else
      //        _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(parameters.getStandardParallel1(), useNSEW, useMinutes, useSeconds));
          /* std parallel 2 = 89 59 59.0 */
    //      if (northHemi){System.out.println("n");
              stdParallel2NeysParamsTextField.setText(jniStrtoval.JNILatitudeToString(89.99944444444444, false, useMinutes, useSeconds));
    //      else {System.out.println("s");
    //          stdParallel2NeysParamsTextField.setText(jniStrtoval.JNILatitudeToString(-89.99944444444444, useNSEW, useMinutes, useSeconds));}
          _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(parameters.getFalseEasting()));
          _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(parameters.getFalseNorthing()));
          break;
        }
        case CoordinateTypes.OMERC:
        {
          ObliqueMercatorParameters parameters = (ObliqueMercatorParameters)_parameters;
          _4ParamFieldsRow1TextFieldA.setText(jniStrtoval.JNILatitudeToString(parameters.getOriginLatitude(), useNSEW, useMinutes, useSeconds));

          jniStrtoval.setNumberFormat(_4ParamFieldsRow1TextFieldB, parameters.getScaleFactor(), 5);

          _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILongitudeToString(parameters.getLongitude1(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow1TextFieldD.setText(jniStrtoval.JNILatitudeToString(parameters.getLatitude1(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow2TextFieldA.setText(jniStrtoval.JNILongitudeToString(parameters.getLongitude2(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNILatitudeToString(parameters.getLatitude2(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(parameters.getFalseEasting()));
          _4ParamFieldsRow2TextFieldD.setText(jniStrtoval.JNIMeterToString(parameters.getFalseNorthing()));
          break;
        }
        case CoordinateTypes.POLARSTEREO:
        {
          PolarStereographicParameters parameters = (PolarStereographicParameters)_parameters;
          _4ParamFieldsRow1TextFieldB.setText(jniStrtoval.JNILongitudeToString(parameters.getLongitudeDownFromPole(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow1TextFieldC.setText(jniStrtoval.JNILatitudeToString(parameters.getLatitudeOfTrueScale(), useNSEW, useMinutes, useSeconds));
          _4ParamFieldsRow2TextFieldB.setText(jniStrtoval.JNIMeterToString(parameters.getFalseEasting()));
          _4ParamFieldsRow2TextFieldC.setText(jniStrtoval.JNIMeterToString(parameters.getFalseNorthing()));
          break;
        }
        case CoordinateTypes.GEODETIC:      
        {
          GeodeticParameters parameters = (GeodeticParameters)_parameters;
          heightComboBox.setSelectedIndex(parameters.getHeightType());
          break;
        }
        case CoordinateTypes.UTM:      
        {

          UTMParameters parameters = (UTMParameters)_parameters;
          if(parameters.getOverride() != 0)
            zoneRadioButton.setSelected(true);
          else
            zoneRadioButton.setSelected(false);
          zoneTextField.setText(String.valueOf(parameters.getZone()));
          break;
        }
      }
    }
    catch(GeotransError e)
    {
      jniStrtoval.displayErrorMsg(this, e.getMessage());
    }
    catch(JNIException e)
    {
      jniStrtoval.displayErrorMsg(this, e.getMessage());
    }
  }
  
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel _3ParamFieldsRow1LabelA;
    private javax.swing.JLabel _3ParamFieldsRow1LabelB;
    private javax.swing.JLabel _3ParamFieldsRow1LabelC;
    private javax.swing.JPanel _3ParamFieldsRow1Panel;
    private javax.swing.JTextField _3ParamFieldsRow1TextFieldA;
    private javax.swing.JTextField _3ParamFieldsRow1TextFieldB;
    private javax.swing.JTextField _3ParamFieldsRow1TextFieldC;
    private javax.swing.JLabel _3ParamFieldsRow2LabelA;
    private javax.swing.JLabel _3ParamFieldsRow2LabelB;
    private javax.swing.JLabel _3ParamFieldsRow2LabelC;
    private javax.swing.JPanel _3ParamFieldsRow2Panel;
    private javax.swing.JTextField _3ParamFieldsRow2TextFieldA;
    private javax.swing.JTextField _3ParamFieldsRow2TextFieldB;
    private javax.swing.JTextField _3ParamFieldsRow2TextFieldC;
    private javax.swing.JLabel _4ParamFieldsRow1LabelA;
    private javax.swing.JLabel _4ParamFieldsRow1LabelB;
    private javax.swing.JLabel _4ParamFieldsRow1LabelC;
    private javax.swing.JLabel _4ParamFieldsRow1LabelD;
    private javax.swing.JPanel _4ParamFieldsRow1Panel;
    private javax.swing.JTextField _4ParamFieldsRow1TextFieldA;
    private javax.swing.JTextField _4ParamFieldsRow1TextFieldB;
    private javax.swing.JTextField _4ParamFieldsRow1TextFieldC;
    private javax.swing.JTextField _4ParamFieldsRow1TextFieldD;
    private javax.swing.JLabel _4ParamFieldsRow2LabelA;
    private javax.swing.JLabel _4ParamFieldsRow2LabelB;
    private javax.swing.JLabel _4ParamFieldsRow2LabelC;
    private javax.swing.JLabel _4ParamFieldsRow2LabelD;
    private javax.swing.JPanel _4ParamFieldsRow2Panel;
    private javax.swing.JTextField _4ParamFieldsRow2TextFieldA;
    private javax.swing.JTextField _4ParamFieldsRow2TextFieldB;
    private javax.swing.JTextField _4ParamFieldsRow2TextFieldC;
    private javax.swing.JTextField _4ParamFieldsRow2TextFieldD;
    private javax.swing.JLabel centralMeridianNeysParamsLabel;
    private javax.swing.JPanel centralMeridianNeysParamsPanel;
    private javax.swing.JTextField centralMeridianNeysParamsTextField;
    private javax.swing.JComboBox datumComboBox;
    private javax.swing.JLabel datumLabel;
    private javax.swing.JPanel datumPanel;
    private javax.swing.JLayeredPane datumSelectLayeredPane;
    private javax.swing.JTextField datumTextField;
    private javax.swing.JLabel ellipsoidLabel;
    private javax.swing.JTextField ellipsoidTextField;
    private javax.swing.JComboBox heightComboBox;
    private javax.swing.JLabel heightLabel;
    private javax.swing.JPanel heightLabelPanel;
    private javax.swing.JPanel heightPanel;
    private javax.swing.JPanel hemiBoxPanel;
    private javax.swing.JLabel inputProjectionLabel;
    private javax.swing.JRadioButton nHemiRadioButton;
    private javax.swing.JRadioButton neys71RadioButton;
    private javax.swing.JRadioButton neys74RadioButton;
    private javax.swing.JPanel neysParamsRow1Panel;
    private javax.swing.JLabel originLatitudeNeysParamsLabel;
    private javax.swing.JPanel originLatitudeNeysParamsPanel;
    private javax.swing.JTextField originLatitudeNeysParamsTextField;
    private javax.swing.JLayeredPane paramFieldsRow1LayeredPane;
    private javax.swing.JLayeredPane paramFieldsRow2LayeredPane;
    private javax.swing.JComboBox projectionComboBox;
    private javax.swing.JPanel projectionPanel;
    private javax.swing.JRadioButton sHemiRadioButton;
    private javax.swing.JPanel stdParallel1NeysParamsPanel;
    private javax.swing.JLabel stdParallel2NeysParamsLabel;
    private javax.swing.JPanel stdParallel2NeysParamsPanel;
    private javax.swing.JTextField stdParallel2NeysParamsTextField;
    private javax.swing.JLabel tempZoneBoxLabel;
    private javax.swing.JPanel zoneBoxPanel;
    private javax.swing.JPanel zoneHemiPanel;
    private javax.swing.JLabel zoneLabel;
    private javax.swing.JRadioButton zoneRadioButton;
    private javax.swing.JLabel zoneRangeLabel;
    private javax.swing.JTextField zoneTextField;
    // End of variables declaration//GEN-END:variables

}
