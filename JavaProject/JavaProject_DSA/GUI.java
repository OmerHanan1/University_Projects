import javax.swing.*;

import java.awt.*;

import javax.swing.border.*;

import java.awt.event.*;
import java.io.*;
import java.util.ArrayList;
import java.awt.image.*;


@SuppressWarnings({ "rawtypes", "unchecked" })
public class GUI extends JFrame implements MyInterface{
/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	/////////////////////////////////////////////////////////////////////////
////                   2 vars  - DONT TOUCH                          
/////////////////////////////////////////////////////////////////////////
	String fileName="db1.txt"; 
	boolean withOutLoading=false;
	
	public void setWithOutLoading(boolean withOutLoading){
		this.withOutLoading = withOutLoading; 
	}



/////////////////////////////////////////////////////////////////////////
////                    START GUI  - DONT TOUCH                          
/////////////////////////////////////////////////////////////////////////
	MyInterface studentSolution = new StudentSolution();
	
    ImageIcon myImageIcon;
    JPanel mainPanel = new JPanel();
    JPanel inputListPanel = new JPanel();
    JPanel outputListPanel = new JPanel();
    BorderLayout borderLayout1 = new BorderLayout();
    BorderLayout borderLayout2 = new BorderLayout();
    BorderLayout borderLayout3 = new BorderLayout();
    Border border1, border2, border3;
    JMenuBar jMenuBar = new JMenuBar();
    JMenu inputMenu, workingModes;
    JCheckBoxMenuItem loadPictureMenuItem, loadTXTMenuItem;
    JRadioButtonMenuItem firstSolution, secondSolution;
    JScrollPane inputListScrollPane;
    JScrollPane outputListScrollPane;
    String[] data = {"==="};
    JList inputList = new JList();
    JList outputList = new JList(data);
    TitledBorder titledBorder1, titledBorder2, titledBorder3, titledBorder4, titledBorder5, titledBorder6, titledBorder7;
    FlowLayout flowLayout1 = new FlowLayout();
    PicturePanel picturePanel = new PicturePanel(this);
/////////////////////////////////////////////////////////////////////////
////                    END GUI    - DONT TOUCH                                     
/////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
////           Construct the application  - DONT TOUCH                          
/////////////////////////////////////////////////////////////////////////
    public GUI() {

        try {
            jbInit();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

/////////////////////////////////////////////////////////////////////////
////           Main method    - DONT TOUCH                     
/////////////////////////////////////////////////////////////////////////
    public static void main(String[] args) {
        try {
            GUI myGUI = new GUI();
            myGUI.setSize(1000, 900);
            myGUI.setResizable(false);
            myGUI.setTitle("Assignment no. 4");
            myGUI.setVisible(true);

        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }


/////////////////////////////////////////////////////////////////////////
////           GUI method    - DONT TOUCH                     
/////////////////////////////////////////////////////////////////////////
    private void jbInit() throws Exception {
        titledBorder1 = new TitledBorder("");
        titledBorder2 = new TitledBorder("");
        titledBorder3 = new TitledBorder("");
        titledBorder4 = new TitledBorder(BorderFactory.createEtchedBorder(Color.white, new Color(148, 145, 140)), "Output list");
        border1 = BorderFactory.createEtchedBorder(Color.white, new Color(148, 145, 140));
        titledBorder5 = new TitledBorder(BorderFactory.createEtchedBorder(Color.white, new Color(148, 145, 140)), "Input list   ");
        border2 = BorderFactory.createEmptyBorder();
        titledBorder6 = new TitledBorder(border2, "My Picture");
        border3 = BorderFactory.createEmptyBorder();
        titledBorder7 = new TitledBorder(BorderFactory.createMatteBorder(6, 6, 6, 6, Color.red), "DS21");
        titledBorder7.setTitleFont(new Font("SansSerif", Font.BOLD, 30));
        mainPanel.setLayout(borderLayout1);
        this.getContentPane().setLayout(borderLayout2);
        this.getContentPane().setBackground(new Color(212, 224, 200));
        this.setJMenuBar(jMenuBar);
        JScrollPane inputListScrollPane = new JScrollPane(inputList);
        JScrollPane outputListScrollPane = new JScrollPane(outputList);
        inputListPanel.setLayout(flowLayout1);
        inputListPanel.setBackground(new Color(255, 175, 122));
        inputListPanel.setBorder(titledBorder5);
        inputListPanel.setPreferredSize(new Dimension(150, 250));
        outputListPanel.setBackground(Color.orange);
        outputListPanel.setBorder(titledBorder4);
        outputListPanel.setLayout(borderLayout3);
        mainPanel.setBackground(new Color(228, 208, 200));
        mainPanel.setBorder(titledBorder7);
        inputListScrollPane.setPreferredSize(new Dimension(140, 250));
        this.getContentPane().add(mainPanel, BorderLayout.CENTER);
        mainPanel.add(picturePanel, BorderLayout.CENTER);
        mainPanel.add(inputListPanel, BorderLayout.EAST);
        inputListPanel.add(inputListScrollPane, null);
        inputMenu = new JMenu("Input Menu");
        workingModes = new JMenu("Working Modes - Running Time");
        jMenuBar.add(inputMenu);
        jMenuBar.add(workingModes);
        loadPictureMenuItem = new JCheckBoxMenuItem("Load The Picture");
        loadPictureMenuItem.addActionListener(new GUI_loadPictureMenuItem_actionAdapter(this));
        inputMenu.add(loadPictureMenuItem);
        inputMenu.addSeparator();
        loadTXTMenuItem = new JCheckBoxMenuItem("Load The TXT DB For Points");
        loadTXTMenuItem.addActionListener(new GUI_loadTXTMenuItem_actionAdapter(this));
        inputMenu.add(loadTXTMenuItem);
        ButtonGroup group = new ButtonGroup();
        firstSolution = new JRadioButtonMenuItem("firstSolution");
        firstSolution.setSelected(true);
        group.add(firstSolution);
        workingModes.add(firstSolution);
        secondSolution = new JRadioButtonMenuItem("secondSolution");
        group.add(secondSolution);
        workingModes.add(secondSolution);
        mainPanel.add(outputListPanel, BorderLayout.SOUTH);
        outputListPanel.add(outputListScrollPane, BorderLayout.CENTER);
    }
    
    
    
/////////////////////////////////////////////////////////////////////////
////           load Picture method    - DONT TOUCH                     
/////////////////////////////////////////////////////////////////////////
    void loadPictureMenuItem_actionPerformed(ActionEvent e) {

        JFileChooser fc = new JFileChooser();
        int returnVal = fc.showOpenDialog(this);

        if (returnVal == JFileChooser.APPROVE_OPTION) {
            File file = fc.getSelectedFile();
            picturePanel.loadPicture(file.getAbsolutePath());
            loadPictureMenuItem.setState(true);
        } else
            loadPictureMenuItem.setState(false);
    }



/////////////////////////////////////////////////////////////////////////
////           load txt DB method    - DONT TOUCH                  
/////////////////////////////////////////////////////////////////////////
    void loadTXTMenuItem_actionPerformed(ActionEvent e) {
		try {
    		BufferedReader input=null;
    		int returnVal=0;
    		JFileChooser fc=null;
    		File file=null;
    	
    		if(withOutLoading){input = new BufferedReader(new FileReader(fileName));}
    		else{fc = new JFileChooser();	returnVal = fc.showOpenDialog(this);}
    	
        	if (returnVal == JFileChooser.APPROVE_OPTION || withOutLoading) {
            	if(!withOutLoading) file = fc.getSelectedFile();

                if (!withOutLoading) input = new BufferedReader(new FileReader(file));
                String line = null;
                String objectName;
                int objectX, objectY;
                ArrayList<String> inputPoints = new ArrayList<String>();

                while ((line = input.readLine()) != null) {
                    String[] lineArray = line.split(" ");
                    objectName = lineArray[0];
                    objectX = Integer.parseInt(lineArray[1].split("=")[1]);
                    objectY = Integer.parseInt(lineArray[2].split("=")[1]);
                    inputPoints.add(line);
                    
                    insertDataFromDBFile (objectName, objectX, objectY);

                 }           
                updateInputList( inputPoints.toArray());
            }
            loadTXTMenuItem.setState(true);
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
    }



/////////////////////////////////////////////////////////////////////////
////           update the input List method    - DONT TOUCH                     
/////////////////////////////////////////////////////////////////////////
	public void updateInputList(Object[] inputPoints){
		inputList = new JList(inputPoints);
        inputListScrollPane = new JScrollPane(inputList);
        inputListScrollPane.setPreferredSize(new Dimension(140, 250));
        inputListPanel.remove(0);
        inputListPanel.add(inputListScrollPane, null);
        inputListPanel.repaint();
        setVisible(true);
       // repaint();
	}
	
/////////////////////////////////////////////////////////////////////////
////           update the output List method    - DONT TOUCH                     
/////////////////////////////////////////////////////////////////////////
	public void updateOutputList(String[] outputPoints){
		outputList = new JList(outputPoints);
        outputListScrollPane = new JScrollPane(outputList);
        outputListScrollPane.setPreferredSize(new Dimension(140, 250));
        outputListPanel.remove(0);
        outputListPanel.add(outputListScrollPane, null);
        outputListPanel.repaint();
        setVisible(true);
	}

	@Override
	public String[] firstSolution(int leftTopX, int leftTopY, int rightBottomX,
			int rightBottomY) {
		return studentSolution.firstSolution(leftTopX, leftTopY, rightBottomX, rightBottomY);
	}

	@Override
	public String[] secondSolution(int leftTopX, int leftTopY,
			int rightBottomX, int rightBottomY) {
		return studentSolution.secondSolution(leftTopX, leftTopY, rightBottomX, rightBottomY);
	}


	
	@Override
	public void insertDataFromDBFile(String objectName, int objectX, int objectY) {
		studentSolution.insertDataFromDBFile(objectName, objectX, objectY);
	}


}



////////////////////////////////////////////////////////////////
////////////////DONT TOUCH THIS CLASS!!!! //////////////////////
////////////////////////////////////////////////////////////////

@SuppressWarnings("serial")
class PicturePanel extends JPanel implements MouseListener, MouseMotionListener {

    private BufferedImage image;
//    private Rectangle imageRect;
//    private TexturePaint imagePaint2;

    boolean loaded = false;

    int startX, startY, startY_origin;
    int tmpX, tmpY, tempY_origin;
    boolean drawingNow = false;
    GUI myGUI;

    public PicturePanel(GUI myGUI) {
        this.myGUI = myGUI;
    }

    public void loadPicture(String path) {
        image = getBufferedImage(path, this);
        addMouseListener(this);
        addMouseMotionListener(this);
        loaded = true;
        repaint();
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (!loaded) return;
        Graphics2D g2d = (Graphics2D) g;

        g2d.drawImage(image, 0, 0, image.getWidth(), image.getHeight(), null);
        g2d.setPaint(Color.red);
        g2d.setStroke(new BasicStroke(6)); // 6-pixel wide pen
        if (drawingNow)
            g2d.drawRect(Math.min(startX, tmpX), Math.min(startY_origin, tempY_origin), Math.abs(startX - tmpX), Math.abs(startY_origin - tempY_origin));
    }

    public void mousePressed(MouseEvent e) {
        startX = e.getX();
        startY = Math.abs(e.getY() - image.getHeight());
        startY_origin = e.getY();
        drawingNow = true;
    }

    public void mouseReleased(MouseEvent e) {
        System.out.println("startX " + startX);
        System.out.println("startY " + startY);
        System.out.println("tmpX " + tmpX);
        System.out.println("tmpY " + tmpY);
        drawingNow = false;
        /// now we should calc the points that in range
        //   int (startX, startY) , (tmpX, tmpY);
        if(myGUI.firstSolution.isSelected()) 
        myGUI.updateOutputList(	myGUI.firstSolution(Math.min(startX,tmpX),Math.max(startY,tmpY),
        		Math.max(startX,tmpX),Math.min(startY,tmpY)));
        if(myGUI.secondSolution.isSelected())
        myGUI.updateOutputList(myGUI.secondSolution(Math.min(startX,tmpX),Math.max(startY,tmpY),
        		Math.max(startX,tmpX),Math.min(startY,tmpY)));
    }
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
    public void mouseClicked(MouseEvent e) {}
    public void mouseDragged(MouseEvent e) {repaint();tmpX = e.getX();tmpY = Math.abs(e.getY() - image.getHeight());tempY_origin=e.getY();}
    public void mouseMoved(MouseEvent e) {}
	public static BufferedImage getBufferedImage(String imageFile,Component c) {
        Image image = c.getToolkit().getImage(imageFile);
        waitForImage(image, c);
        BufferedImage bufferedImage =new BufferedImage(image.getWidth(c), image.getHeight(c), BufferedImage.TYPE_INT_RGB);
        Graphics2D g2d = bufferedImage.createGraphics();
        g2d.drawImage(image, 0, 0, c);
        return (bufferedImage);
    }
    public static boolean waitForImage(Image image, Component c) {
        MediaTracker tracker = new MediaTracker(c);
        tracker.addImage(image, 0);
        try { tracker.waitForAll();} catch (InterruptedException ie) {}
        return (!tracker.isErrorAny());
    }
}
////////////////////////////////////////////////////////////////
////////////////DONT TOUCH THIS CLASS!!!! //////////////////////
////////////////////////////////////////////////////////////////
class GUI_loadPictureMenuItem_actionAdapter implements java.awt.event.ActionListener {
    GUI adaptee;

    GUI_loadPictureMenuItem_actionAdapter(GUI adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.loadPictureMenuItem_actionPerformed(e);
    }
}
////////////////////////////////////////////////////////////////
////////////////DONT TOUCH THIS CLASS!!!! //////////////////////
////////////////////////////////////////////////////////////////
class GUI_loadTXTMenuItem_actionAdapter implements java.awt.event.ActionListener {
    GUI adaptee;

    GUI_loadTXTMenuItem_actionAdapter(GUI adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.loadTXTMenuItem_actionPerformed(e);
    }
}
    
    
    
    
    
