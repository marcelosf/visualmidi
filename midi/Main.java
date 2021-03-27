package proj;

import proj.musicxml.MusicXMLDocument;
import proj.util.XMLReader;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.*;
import javax.sound.midi.*;
import javax.swing.*;
import javax.imageio.ImageIO;

import org.w3c.dom.Document;

@SuppressWarnings("serial")
public class Main	extends JFrame	implements ActionListener
{
	private Player player;
	JButton BotaoMidi, BPlay, BStop, cap;
	BufferedImage img;
	File ImgPart;

//Construtor dos atributos que compoem os programas: botõees, rótulos, painéis;   
	public Main()
	{
		this.setMinimumSize(new Dimension(300, 100));
		this.setLocationRelativeTo(null);
		Container caixa = getContentPane();
		caixa.setLayout(new BorderLayout());
		Container painel = new Container();
		painel.setLayout(new GridLayout(2,1));
		caixa.add(painel, BorderLayout.SOUTH);
		BotaoMidi = new JButton("Gerar MIDI");
		BPlay = new JButton("Tocar");
		BStop = new JButton("Parar");
		cap = new JButton("importar");
		painel.add(BotaoMidi);
		painel.add(BPlay);
		painel.add(BStop);
		painel.add(cap);
		BotaoMidi.addActionListener(this);
		BPlay.addActionListener(this);
		BStop.addActionListener(this);
		cap.addActionListener(this);
	}

//Execução da conversão do arquixo xml em midi.   
	public void BotaoConverte()
	{
		try
		{ 
			Document Xml = XMLReader.LerArquivo("Partitura.xml");
			MusicXMLDocument Mxml = new MusicXMLDocument(Xml);
			Sequence SeqXml = MusicXMLtoMIDI.convertMusicXMLtoMIDI(Mxml, player);
			MidiSystem.write(SeqXml, 1, new File("Musica.mid"));
		}
		catch (Exception ex)
		{}
	}
  
//Botão para Conversão musicxml para midi.
	public void actionPerformed(ActionEvent e)
	{
		if(e.getSource() == BotaoMidi)
			BotaoConverte();
		
		if(e.getSource() == BPlay)
			player.play();
		
		if(e.getSource() == BStop)
			player.stop();
		
		if(e.getSource() == cap)
		{
			ImgPart = getFile();
			try {
					img = ImageIO.read(ImgPart);
				       File newFile = (File)ImgPart.getAbsoluteFile();
				       //File dir = new File("c:\\" );
				       boolean success = newFile.renameTo(new File("imagem.jpg"));
				       //boolean success = newFile.renameTo(new File(dir, "imagem.jpg"));
				       if( !success ){
				               System.out.println("N�o copiou!!!!!!!");
				       }
					//repaint();
				} catch (IOException ImgPart)
				{ }
		}	
	
	}

	//Método usado para obter o caminho do arquivo
	public File getFile()
	{
	JFileChooser fileChooser = new JFileChooser();
	fileChooser.setFileSelectionMode(
	JFileChooser.FILES_ONLY );
	int result = fileChooser.showOpenDialog( this );
	 if ( result == JFileChooser.CANCEL_OPTION )
	 return null;
	else
	 return fileChooser.getSelectedFile();
	}
	
// Função principal da parte java. 
	public static void main(String[] args)
	{
		Main xmlMain = new Main();
		xmlMain.setVisible(true);
	}
}