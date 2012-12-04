/*
 * FillList.java
 *
 * Created on April 26, 2001, 1:49 PM
 */

package geotrans.gui;


import geotrans.enumerations.ListType;
import geotrans.jni.*;


/**
 *
 * @author  amyc
 * @version 
 */
public class FillList extends Object {

    private JNIEngine jniEngine = new JNIEngine();
    private JNIStrtoval jniStrtoval = new JNIStrtoval();
    private long datumCount = 0;

    /** Creates new FillList */
    public FillList(javax.swing.JComboBox list, int listType) {
        if (listType == ListType.DATUM)
            fillDatumList(list);
        else 
            fillEllipsoidList(list);    
    }

    private void fillDatumList(javax.swing.JComboBox datumList)
    {
        try
        {
          if(datumList.getItemCount() > 0)
            datumList.removeAllItems();
          
            java.lang.String datumCode = "";
            java.lang.String datumName = "";
            datumCount = jniEngine.JNIGetDatumCount();//System.out.println("count: " + datumCount);
            for (int i = 1; i <= datumCount; i++) 
            {
              datumCode = jniEngine.JNIGetDatumCode(i);//System.out.println("code: " + datumCode);
              datumName = jniEngine.JNIGetDatumName(i); 
              datumList.addItem(datumCode + ":  " + datumName);
            }
            // set to WGS 84
            datumList.setSelectedIndex((int)jniEngine.JNIGetDatumIndex ("WGE") - 1);
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(new javax.swing.JFrame(), e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.displayErrorMsg(new javax.swing.JFrame(), e.getMessage());
        }
        
    }
    
    
    private void fillEllipsoidList(javax.swing.JComboBox ellipsoidList)
    {
        try
        {
            java.lang.String ellipsoidCode = "";
            java.lang.String ellipsoidName = "";
            long ellipsoidCount = jniEngine.JNIGetEllipsoidCount();
            for (int i = 1; i <= ellipsoidCount; i++) 
            {
              ellipsoidCode = jniEngine.JNIGetEllipsoidCode(i);
              ellipsoidName = jniEngine.JNIGetEllipsoidName(i); 
              ellipsoidList.addItem(ellipsoidCode + ":  " + ellipsoidName);
            }
            // set to WGS 84
            ellipsoidList.setSelectedIndex((int)jniEngine.JNIGetEllipsoidIndex ("WE") - 1);
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(new javax.swing.JFrame(), e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.displayErrorMsg(new javax.swing.JFrame(), e.getMessage());
        }
    }
    
    public void addDatum(javax.swing.JComboBox datumList)
    {
        try
        {
            long newDatumCount = jniEngine.JNIGetDatumCount();
            if (datumCount < newDatumCount)
            {
                java.lang.String datumCode = "";
                java.lang.String datumName = "";
                for (int i = (int)datumCount; i < newDatumCount; i++)
                {
                    datumCode = jniEngine.JNIGetDatumCode(i + 1);
                    datumName = jniEngine.JNIGetDatumName(i + 1); 
                    datumList.insertItemAt(datumCode + ":  " + datumName, i);
                }
            datumCount = newDatumCount;
            }
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(new javax.swing.JFrame(), e.getMessage());
        }
        catch(JNIException e)
        {
            jniStrtoval.displayErrorMsg(new javax.swing.JFrame(), e.getMessage());
        }
    }
    
    public void deleteDatum(javax.swing.JComboBox datumList, int index)
    {
        try
        {
            long newDatumCount = jniEngine.JNIGetDatumCount();
            
            if (datumCount > newDatumCount)
            {
                datumList.removeItemAt(index);
                datumCount --;
            }
        }
        catch(GeotransError e)
        {
            jniStrtoval.displayErrorMsg(new javax.swing.JFrame(), e.getMessage());
        }
    }
    
}

