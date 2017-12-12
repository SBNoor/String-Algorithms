import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class BorderArray {
	
	public static final String nucleotide = "a";
	
	public static String randomAlphaNumeric(int count) {
		StringBuilder builder = new StringBuilder();
		while (count-- != 0) {
		int character = (int)(Math.random()*nucleotide.length());
		builder.append(nucleotide.charAt(character));
		}
			return builder.toString();
}
	
	public static void search_naive(StringBuilder text, StringBuilder pattern)
	{
		int text_len = text.length();
		int pattern_len = pattern.length();
		int k = 1;
		
		for(int i=0;i<=text_len - pattern_len;i++)
		{
			int j;
			for(j=0;j<pattern_len;j++)
			{
				if(text.charAt(i+j) != pattern.charAt(j))
				{
					break;
				}
				
			}
			
			if(j == pattern_len)
			{
				System.out.println(k + ") "+ "Pattern found at : " + (i + 1));
				k++;
			}

		}
	}
	
	public static int[] buildPrefixArray(StringBuilder pattern)
	{
		int[] prefixArray = new int[pattern.length()];
		int j = 0;
		int i = 1;
		prefixArray[0] = 0;
		while(i < pattern.length())
		{
			if(pattern.charAt(i) == pattern.charAt(j))
			{
				prefixArray[i] = j + 1;
				i++;
				j++;
			}
			else
			{
				if(j > 0)
				{
					j = prefixArray[j-1];
				}
				if(j == 0)
				{
					prefixArray[i] = j;
					i++;
				}
			}
			//counter++;
		} // end of while loop
		

		
		return prefixArray;
		
	}
	
	public static void search_KMP(int[] prefixArray, StringBuilder pattern, StringBuilder text)
	{
		int j = 0;
		int i = 0;
		int k = 1;
		while(i<text.length())
		{
			if(text.charAt(i) == pattern.charAt(j))
			{
				i++;
				j++;
			}
			if(j == pattern.length())
			{
				System.out.println(k + ") Pattern found at : " + ((i-j)+1));
				j = prefixArray[j-1];
				k++;
			}

			else if(i < text.length() && pattern.charAt(j) != text.charAt(i))
			{
				if(j > 0)
				{
					j = prefixArray[j-1];
				}
				else
				{
					i++;
				}
			}
				
		}
		
	}
	
	
	public static void search_BA(StringBuilder str, StringBuilder pattern)
	{
		
		int k = 1;
		
		String concatenatedString = "h" + pattern + "$" + str;
		
		char[] text = concatenatedString.toCharArray();
		
		int b = 0;
		
		int[] border = new int[text.length];

		border[0] = -1;
		border[1] = 0;
		
		for(int i=1;i<text.length-1;i++)
		{
			b = border[i];
			while(b > 0 && text[i+1] != text[b+1])
			{
				b = border[b];
				
			}
			if(text[i+1] == text[b+1])
			{
				border[i+1] = b+1;
			}
			else
			{
				border[i+1] = 0;
			}
		}
		
		int length = pattern.length();
		
		for(int i=0;i<text.length;i++)
		{
			if(border[i] == length)
			{
				System.out.println(k + ")" + "Pattern found at : " + ((i-2*length - 1)+1));
				k++;
			}
		}
	}
	
	public static void main(String[] args)
	{
		
		try
		{	
		System.out.println("Enter as follows:");
		System.out.println("<filename>/txt");
		System.out.println("<pattern>.txt");
		System.out.println("Name of the function i.e. search_naive, search_BA, or search_KMP");
		Scanner input = new Scanner(System.in);
		String input_text = input.nextLine();
		
		StringBuilder text = new StringBuilder("");
				
		FileReader fr = new FileReader(input_text);
		BufferedReader br = new BufferedReader(fr);
		
		for (String line; (line = br.readLine()) != null; )
		{
			if(line.trim().equals("\n") || line.trim().equals("\t"))
			{
				text.append(" ");
				
			}
			else
			{
				text.append(line + " ");
			}
			
		}
		
		input_text = input.nextLine();
		//input.close();
		
		StringBuilder pattern = new StringBuilder("");
		fr  = new FileReader(input_text);
		br = new BufferedReader(fr);
		
		for (String line; (line = br.readLine()) != null; )
		{
			if(line.isEmpty() || line.trim().equals("")|| line.trim().equals("\n\n") || line.trim().equals("\t"))
			{
				pattern.append('\n');
			}
			else
			{
				pattern.append(line);
			}
			
		}
		br.close();
		
		String input_func = input.nextLine();
		
		switch(input_func){
		
		case "search_BA":
			
			search_BA(text,pattern);
			break;
			
		case "search_KMP":
			int[] prefixArray =  buildPrefixArray(pattern);
			search_KMP(prefixArray,pattern,text);
			break;
			
		case "search_naive":
			search_naive(text,pattern);
			break;
		
		}
       
		}
		catch(IOException e)
		{
			System.out.println(e.getMessage());
		}
	}

}
