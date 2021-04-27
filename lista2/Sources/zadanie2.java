import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class zadanie2{
	static long comparesMerge = 0;
	static long swapsMerge = 0;
	static long startTimeMerge = 0;
	static long endTimeMerge = 0;
	
	static long comparesQuick = 0;
	static long swapsQuick = 0;
	static long startTimeQuick = 0;
	static long endTimeQuick = 0;
	
	//static long compares = 0;
	//static long swaps = 0;
	//static long startTime = 0;
	//static long endTime = 0;
	
	static String sortType = "";
	static String order = "";
	static String out = "";
	
	public static String InsertionSort(ArrayList<Integer> tab, String comp) throws Exception
	{
		long startTime = System.nanoTime();
		long compares = 0;
		long swaps = 0;
		
		for(int i = 1; i < tab.size(); i++)
		{
			int key = tab.get(i);
			int j = i-1;
			compares++;
			while( (j >= 0) && (tab.get(j) >= key) )
			{
				//System.err.println("comp " + key + " " + tab.get(j));
				compares++;
				tab.set(j+1, tab.get(j));
				swaps++;
				//System.err.println("swap "  + tab.get(j+1) + " " + tab.get(j));
				j--;
			}
			tab.set(j+1, key);
			swaps++;
		}
		long endTime = System.nanoTime();
		long diff = endTime - startTime;
		String ans = compares + ";" + swaps + ";" + diff + ";";
		boolean check = true;
		for(int i = 1; i < tab.size(); i++)
		{
			if(tab.get(i-1) > tab.get(i))
			{
				check = false;
				break;
			}
		}
		if(!check)
		{
			throw new Exception();
		}
		else 
		{
			return ans;
		}
		
	}
	
	public static void Merge(ArrayList<Integer> tab, int start, int mid, int end, String comp) throws Exception
	{
		int newStart = mid + 1;
		comparesMerge ++;
		//System.err.println("comp " + tab.get(mid) + " " + tab.get(newStart));
		if(tab.get(mid) <= tab.get(newStart) )return;
		
		while(start <= mid && newStart <= end)
		{	
			comparesMerge ++;
			//System.err.println("comp " + tab.get(start) + " " + tab.get(newStart));
			if(tab.get(start) <= tab.get(newStart))
			{
				start++;
			}
			else
			{
				int val = tab.get(newStart);
				int index = newStart;
				
				while(index != start)
				{
					swapsMerge++;
					//System.err.println("swap " + tab.get(index) + " " + tab.get(index -1));
					tab.set(index, tab.get(index -1));
					index --;
				}
				swapsMerge++;
				//System.err.println("swap " + tab.get(start) + " " + val);
				tab.set(start, val);
				start++;
				mid++;
				newStart++;
			}
		}
	}
	
	public static void MergeSort(ArrayList<Integer> tab, int left, int right, String comp) throws Exception
	{
		if(left < right)
		{
			int mid = (left + right) / 2;
			MergeSort(tab, left, mid, comp);
			MergeSort(tab, mid+1, right, comp);
			Merge(tab, left, mid, right, comp);
		}
	}
	
	public static String MegreInit(ArrayList<Integer> tab, String comp) throws Exception
	{
		startTimeMerge = System.nanoTime();
		comparesMerge = 0;
		swapsMerge = 0;
		int left = 0;
		int right = tab.size()-1;
		MergeSort(tab, left, right, comp);
		endTimeMerge = System.nanoTime();
		long diff = endTimeMerge - startTimeMerge;
		double time = diff/1000000;
		//System.err.println("comps: " + compares + " swaps: " + swaps + " time: " + time + "ms");
		boolean check = true;
		String ans = comparesMerge + ";" + swapsMerge + ";" + diff + ";";
		for(int i = 1; i < tab.size(); i++)
		{
			if(tab.get(i-1) > tab.get(i))
			{
				check = false;
				break;
			}
		}
		if(!check)
		{
			throw new Exception();
		}
		else
		{
			return ans;
		}
	}
	
	public static int Partition(ArrayList<Integer> tab, int left, int right, String comp) throws Exception
	{
		int pivot = tab.get(right);
		int i = left - 1;
		
		for(int j = left; j < right; j++)
		{
			comparesQuick++;
			//System.err.println("comp " + tab.get(j) + " " + pivot);
			if(tab.get(j) <= pivot)
			{
				i++;
				int swp = tab.get(i);
				swapsQuick++;
				//System.err.println("swap " + tab.get(i) + " " + tab.get(j));
				tab.set(i, tab.get(j));
				tab.set(j, swp);
			}
		}
		
		int swp = tab.get(i+1);
		swapsQuick++;
		//System.err.println("swap " + swp + " " + tab.get(right));
		tab.set(i+1, tab.get(right));
		tab.set(right, swp);
		
		return i+1;
	}
	
	public static void QuickSort(ArrayList<Integer> tab, int left, int right, String comp) throws Exception
	{
		if(left < right)
		{
			int pivot = Partition(tab, left, right, comp);
			
			QuickSort(tab, left, pivot -1, comp);
			QuickSort(tab, pivot + 1, right, comp);
		}
	}
	
	public static String QuickInit(ArrayList<Integer> tab, String comp) throws Exception
	{
		comparesQuick = 0;
		swapsQuick = 0;
		startTimeQuick = System.nanoTime();
		int left =0;
		int right = tab.size()-1;
		QuickSort(tab, left, right, comp);
		endTimeQuick = System.nanoTime();
		long diff = endTimeQuick - startTimeQuick;
		double time = diff/1000000;
		String ans = comparesQuick + ";" + swapsQuick + ";" + diff + ";";
		//System.err.println("comps: " + compares + " swaps: " + swaps + " time: " + time + "ms");
		boolean check = true;
		for(int i = 1; i < tab.size(); i++)
		{
			if(tab.get(i-1) > tab.get(i))
			{
				check = false;
				break;
			}
		}
		if(!check)
		{
			throw new Exception();
		}
		else
		{
			return ans;
		}
	}
	
	public static ArrayList<Integer> RandomArrayGenerator(int N, int a, int b)
	{
		ArrayList<Integer> array= new ArrayList<Integer>();
		Random random = new Random();
		for(int i = 0; i< N ; i++)
		{
			int val = random.nextInt(b-1) + a;
			array.add(val);
		}
		return array;
	}
	
	public static void Testing(int k) throws Exception
	{
		int min = 1;
		int max = 1000000;
		for(int i = 100; i <= 10000; i+=100)
		{
			double cp1=0, cp2=0, cp3=0;
			double swp1=0, swp2=0, swp3=0;
			double diff1=0, diff2=0, diff3=0;
			System.err.println("n = " + i);
			for(int rep = 0; rep < k; rep++)
			{
				ArrayList<Integer> insert = new ArrayList<Integer>(), merge = new ArrayList<Integer>(), 
						quick = new ArrayList<Integer>(), ctrl = new ArrayList<Integer>();
				ctrl = RandomArrayGenerator(i, min, max);
				for(int j = 0; j < i; j++)
				{
					insert.add(ctrl.get(j));
					merge.add(ctrl.get(j));
					quick.add(ctrl.get(j));
				}
				String out1 = InsertionSort(insert, "<=");
				String out2 = MegreInit(merge, "<=");
				String out3 = QuickInit(quick, "<=");
				String[] ans1, ans2, ans3;
				ans1 = out1.split(";");
				ans2 = out2.split(";");
				ans3 = out3.split(";");
				cp1 += (double)Integer.parseInt(ans1[0])/k;
				cp2 += (double)Integer.parseInt(ans2[0])/k;
				cp3 += (double)Integer.parseInt(ans3[0])/k;
				swp1 += (double)Integer.parseInt(ans1[1])/k;
				swp2 += (double)Integer.parseInt(ans2[1])/k;
				swp3 += (double)Integer.parseInt(ans3[1])/k;
				diff1 += (double)Integer.parseInt(ans1[2])/k;
				diff2 += (double)Integer.parseInt(ans2[2])/k;
				diff3 += (double)Integer.parseInt(ans3[2])/k;
			}
			String out1 = (long)cp1 + ";" + (long)swp1 + ";" + (long)diff1 + ";";
			String out2 = (long)cp2 + ";" + (long)swp2 + ";" + (long)diff2 + ";";
			String out3 = (long)cp3 + ";" + (long)swp3 + ";" + (long)diff3 + ";";
			String out = i + ";" + out1 + out2 + out3;
			System.out.println(out);
		}
	}
	
	public static void main(String[] args) throws Exception {
		
		//for(int i = 0; i< args.length; i++)System.out.println(args[i]);
		
		for(int i = 0; i < args.length; i++)
		{
			if(args[i].equals("stat"))
			{
				out = args[i+1];
				int k = Integer.parseInt(args[i+2]);
				Testing(k);
				return;
			}
			if(args[i].equals("type"))
			{
				i++;
				sortType = args[i];
			}
			else if(args[i].equals("comp"))
			{
				i++;
				order = args[i];
			}
		}
		
		int n = 0;
		
		Scanner scanner = new Scanner(System.in);
		
		n = scanner.nextInt();
		ArrayList<Integer> tab = new ArrayList<Integer>();
		
		for(int i = 0; i <  n; i++)
		{
			int tmp = scanner.nextInt();
			tab.add(tmp);
		}
		
		if(sortType.equals("quick"))
		{
			System.out.println("\n QuickSort");
			QuickInit(tab, order);
		}
		else if(sortType.equals("merge"))
		{
			System.out.println("\n MergeSort");
			MegreInit(tab, order);
		}
		else if(sortType.equals("insert"))
		{
			System.out.println("\n Sort");
			InsertionSort(tab, order);
		}
		scanner.close();
	}
}
