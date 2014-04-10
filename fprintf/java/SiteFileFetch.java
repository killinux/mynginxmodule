import java.io.*;    
import java.net.*;    
public class SiteFileFetch extends Thread {    
    SiteInfoBean siteInfoBean = null;     
    long[] nStartPos;   
    long[] nEndPos;   
    FileSplitterFetch[] fileSplitterFetch;   
    long nFileLength;    
    boolean bFirst = true;   
    boolean bStop = false;    
    File tmpFile;   
    DataOutputStream output; //   
    public SiteFileFetch(SiteInfoBean bean) throws IOException    
    {    
        siteInfoBean = bean;    
        //tmpFile = File.createTempFile ("zhong","1111",new File(bean.getSFilePath()));    
        tmpFile = new File(bean.getSFilePath()+File.separator + bean.getSFileName()+".info");   
        if(tmpFile.exists ())    
        {    
            bFirst = false;    
            read_nPos();    
        }    
        else    
        {    
            nStartPos = new long[bean.getNSplitter()];    
            nEndPos = new long[bean.getNSplitter()];    
        }    
    }    
    public void run()    
    {    
        try{    
            if(bFirst)    
            {    
                nFileLength = getFileSize();    
                if(nFileLength == -1)    
                {    
                    System.err.println("File Length is not known!");    
                }    
                else if(nFileLength == -2)    
                {    
                    System.err.println("File is not access!");    
                }    
                else    
                {    
                    for(int i=0;i<nStartPos.length;i++)    
                    {    
                        nStartPos[i] = (long)(i*(nFileLength/nStartPos.length));    
                    }    
                    for(int i=0;i<nEndPos.length-1;i++)    
                    {    
                        nEndPos[i] = nStartPos[i+1];    
                    }    
                    nEndPos[nEndPos.length-1] = nFileLength;    
                }    
            }    
            fileSplitterFetch = new FileSplitterFetch[nStartPos.length];    
            for(int i=0;i<nStartPos.length;i++)    
            {    
                fileSplitterFetch[i] = new FileSplitterFetch(siteInfoBean.getSSiteURL(),    
                        siteInfoBean.getSFilePath() + File.separator + siteInfoBean.getSFileName(),    
                        nStartPos[i],nEndPos[i],i);    
                Utility.log("Thread " + i + " , nStartPos = " + nStartPos[i] + ", nEndPos = "    
                        + nEndPos[i]);    
                fileSplitterFetch[i].start();    
            }    
            // fileSplitterFetch[nPos.length-1] = new FileSplitterFetch(siteInfoBean.getSSiteURL(),   
            //siteInfoBean.getSFilePath() + File.separator    
             //   + siteInfoBean.getSFileName(),nPos[nPos.length-1],nFileLength,nPos.length-1);    
            // Utility.log("Thread " +(nPos.length-1) + ",nStartPos = "+nPos[nPos.length-1]+",   
            //nEndPos = " + nFileLength);    
                // fileSplitterFetch[nPos.length-1].start();    
                //int count = 0;    
                boolean breakWhile = false;    
            while(!bStop)    
            {    
                write_nPos();    
                Utility.sleep(500);    
                breakWhile = true;    
                for(int i=0;i<nStartPos.length;i++)    
                {    
                    if(!fileSplitterFetch[i].bDownOver)    
                    {    
                        breakWhile = false;    
                        break;    
                    }    
                }    
                if(breakWhile)    
                    break;    
                //count++;    
                //if(count>4)    
                // siteStop();    
            }    
            System.err.println("over");    
        }    
        catch(Exception e){e.printStackTrace ();}    
    }    
    public long getFileSize()    
    {    
        int nFileLength = -1;    
        try{    
            URL url = new URL(siteInfoBean.getSSiteURL());    
            HttpURLConnection httpConnection = (HttpURLConnection)url.openConnection ();   
            httpConnection.setRequestProperty("User-Agent","NetFox");    
            int responseCode=httpConnection.getResponseCode();    
            if(responseCode>=400)    
            {    
                processErrorCode(responseCode);    
                return -2; //-2 represent access is error    
            }    
            String sHeader;    
            for(int i=1;;i++)    
            {    
                //DataInputStream in = new DataInputStream(httpConnection.getInputStream ());    
                //Utility.log(in.readLine());    
                sHeader=httpConnection.getHeaderFieldKey(i);    
                if(sHeader!=null)    
                {    
                    if(sHeader.equals("Content-Length"))    
                    {    
                        nFileLength = Integer.parseInt(httpConnection.getHeaderField(sHeader));    
                        break;    
                    }    
                }    
                else    
                    break;    
            }    
        }    
        catch(IOException e){e.printStackTrace ();}    
        catch(Exception e){e.printStackTrace ();}    
        Utility.log(nFileLength);    
        return nFileLength;    
    }    
    private void write_nPos()    
    {    
        try{    
            output = new DataOutputStream(new FileOutputStream(tmpFile));    
            output.writeInt(nStartPos.length);    
            for(int i=0;i<nStartPos.length;i++)    
            {    
                // output.writeLong(nPos[i]);    
                output.writeLong(fileSplitterFetch[i].nStartPos);    
                output.writeLong(fileSplitterFetch[i].nEndPos);    
            }    
            output.close();    
        }    
        catch(IOException e){e.printStackTrace ();}    
        catch(Exception e){e.printStackTrace ();}    
    }    
    private void read_nPos()    
    {    
        try{    
            DataInputStream input = new DataInputStream(new FileInputStream(tmpFile));    
            int nCount = input.readInt();    
            nStartPos = new long[nCount];    
            nEndPos = new long[nCount];    
            for(int i=0;i<nStartPos.length;i++)    
            {    
                nStartPos[i] = input.readLong();    
                nEndPos[i] = input.readLong();    
            }    
            input.close();    
        }    
        catch(IOException e){e.printStackTrace ();}    
        catch(Exception e){e.printStackTrace ();}    
    }    
    private void processErrorCode(int nErrorCode)    
    {    
        System.err.println("Error Code : " + nErrorCode);    
    }    
    public void siteStop()    
    {    
        bStop = true;    
        for(int i=0;i<nStartPos.length;i++)    
            fileSplitterFetch[i].splitterStop();    
    }    
}  
