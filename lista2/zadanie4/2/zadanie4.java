import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class zadanie4{
	static long comparesMerge = 0;
	static long swapsMerge = 0;
	static long startTimeMerge = 0;
	static long endTimeMerge = 0;
	
	static long comparesQuick = 0;
	static long swapsQuick = 0;
	static long startTimeQuick = 0;
	static long endTimeQuick = 0;
	
	static long comparesQuickDual = 0;
	static long swapsQuickDual = 0;
	static long startTimeQuickDual = 0;
	static long endTimeQuickDual = 0;
	
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
	
	public static void swap(ArrayList<Integer> tab, int a, int b)
	{
		swapsQuickDual++;
		int val = tab.get(a);
		tab.set(a, tab.get(b));
		tab.set(b, val);
		return;
	}
	
	public static void QuickDualSort(ArrayList<Integer> tab, int left, int right, int div, String comp) throws Exception
	{
		int len = right - left;
		
		if(len < 1)return;
		
		int third = len / div;
		int m1 = left + third;
		int m2 = right - third;
		
		if(m1 <= left)m1 = left + 1;
		if(m2 >= right)m2 = right - 1;
		comparesQuickDual++;
		if(tab.get(m1) < tab.get(m2))
		{
			swap(tab, m1, left);
			swap(tab, m2, right);
		}
		else
		{
			swap(tab, m1, right);
			swap(tab, m2, left);
		}
		int pivot1 = tab.get(left);
		int pivot2 = tab.get(right);
		
		int l = left + 1;
		int r = right -1;
		for(int k = l; k <= r; k++)
		{
			comparesQuickDual++;
			if(tab.get(k) < pivot1)
			{
				swap(tab, k, l++);
			}
			else if(tab.get(k) > pivot2)
			{
				while(k < r && tab.get(r) > pivot2)
				{
					comparesQuickDual++;
					r--;
				}
				swap(tab, k, r--);
				comparesQuickDual++;
				if(tab.get(k) < pivot1)
				{
					swap(tab, k, l++);
				}
			}
			comparesQuickDual++;
		}
		int dist = r - l;
		if(dist < 13)
		{
			div++;
		}
		swap(tab, l-1, left);
		swap(tab, r+1, right);
		
		QuickDualSort(tab, left, l - 2, div, comp);
		QuickDualSort(tab, r + 2, right, div, comp);
		
		if(dist > len - 13 && pivot1 != pivot2)
		{
			for(int k = l; k < r; k++)
			{
				comparesQuickDual++;
				if(tab.get(k) == pivot1)
				{
					swap(tab, k, l++);
				}
				else if(tab.get(k) == pivot2)
				{
					swap(tab, k, r--);
					if(tab.get(k) == pivot1)
					{
						swap(tab, k, l++);
					}
				}
				comparesQuickDual++;
			}
		}
		if(pivot1 < pivot2)
		{
			QuickDualSort(tab, l, r, div, comp);
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
	
	public static String QuickDualInit(ArrayList<Integer> tab, String comp) throws Exception
	{
		comparesQuickDual = 0;
		swapsQuickDual = 0;
		startTimeQuickDual = System.nanoTime();
		int left = 0;
		int right = tab.size()-1;
		QuickDualSort(tab, left, right, 3, comp);
		endTimeQuickDual = System.nanoTime();
		long diff = endTimeQuickDual - startTimeQuickDual;
		double time = diff/1000000;
		String ans = comparesQuickDual + ";" + swapsQuickDual + ";" + diff + ";";
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
			for(int i = 0; i < tab.size(); i++)
			{
				System.err.print(tab.get(i) + " ");
			}
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
	
	public static ArrayList<String> RandomStringGen(int N, int l)
	{
		ArrayList<String> array = new ArrayList<String>();
		Random random = new Random();
		for(int i = 0; i< N ; i++)
		{
			byte[] ar = new byte[l];
			new Random().nextBytes(ar);
			String val = new String(ar, Charset.forName("UTF-8"));
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
			double cp1=0, cp2=0;
			double swp1=0, swp2=0;
			double diff1=0, diff2=0;
			System.err.println("n = " + i);
			for(int rep = 0; rep < k; rep++)
			{
				ArrayList<Integer> quick = new ArrayList<Integer>(), quickDual = new ArrayList<Integer>(), 
						ctrl = new ArrayList<Integer>();
				ctrl = RandomArrayGenerator(i, min, max);
				String out1 = QuickInsertionInit(ctrl, 7, "<=");
				//String out2 = QuickDualInit(quick, "<=");
				String[] ans1;
				ans1 = out1.split(";");
				//ans2 = out2.split(";");
				cp1 += (double)Integer.parseInt(ans1[0])/k;
				//cp2 += (double)Integer.parseInt(ans2[0])/k;
				swp1 += (double)Integer.parseInt(ans1[1])/k;
				//swp2 += (double)Integer.parseInt(ans2[1])/k;
				diff1 += (double)Integer.parseInt(ans1[2])/k;
				//diff2 += (double)Integer.parseInt(ans2[2])/k;
			}
			String out1 = (long)diff1 + "";
			String out = out1;
			System.out.println(out);
		}
	}
	
	public static void QuickInsertionSort(ArrayList<Integer> tab, int left, int right, int div, int num, String comp)
	{
		int len = right - left;
		if(len < num)
		{
			for(int i = left + 1; i <= right; i++)
			{
				for(int j = i; j > left && tab.get(j) < tab.get(j-1); j--)
				{
					comparesQuickDual++;
					swap(tab, j, j-1);
				}
			}
			return;
		}
		int third = len / div;
		int m1 = left + third;
		int m2 = right - third;
		
		if(m1 <= left)m1 = left + 1;
		if(m2 >= right)m2 = right - 1;
		comparesQuickDual++;
		if(tab.get(m1) < tab.get(m2))
		{
			swap(tab, m1, left);
			swap(tab, m2, right);
		}
		else
		{
			swap(tab, m1, right);
			swap(tab, m2, left);
		}
		int pivot1 = tab.get(left);
		int pivot2 = tab.get(right);
		
		int l = left + 1;
		int r = right -1;
		for(int k = l; k <= r; k++)
		{
			comparesQuickDual++;
			if(tab.get(k) < pivot1)
			{
				swap(tab, k, l++);
			}
			else if(tab.get(k) > pivot2)
			{
				while(k < r && tab.get(r) > pivot2)
				{
					comparesQuickDual++;
					r--;
				}
				swap(tab, k, r--);
				comparesQuickDual++;
				if(tab.get(k) < pivot1)
				{
					swap(tab, k, l++);
				}
			}
			comparesQuickDual++;
		}
		int dist = r - l;
		if(dist < 13)
		{
			div++;
		}
		swap(tab, l-1, left);
		swap(tab, r+1, right);
		
		QuickInsertionSort(tab, left, l - 2, div, num, comp);
		QuickInsertionSort(tab, r + 2, right, div, num, comp);
		
		if(dist > len - 13 && pivot1 != pivot2)
		{
			for(int k = l; k < r; k++)
			{
				comparesQuickDual++;
				if(tab.get(k) == pivot1)
				{
					swap(tab, k, l++);
				}
				else if(tab.get(k) == pivot2)
				{
					swap(tab, k, r--);
					if(tab.get(k) == pivot1)
					{
						swap(tab, k, l++);
					}
				}
				comparesQuickDual++;
			}
		}
		if(pivot1 < pivot2)
		{
			QuickInsertionSort(tab, l, r, div, num, comp);
		}
	}
	
	public static void swapS(ArrayList<String> tab, int a, int b)
	{
		String val = tab.get(a);
		tab.set(a, tab.get(b));
		tab.set(b, val);
	}
	
	public static void QuickInsertionSortStr(ArrayList<String> tab, int left, int right, int div, int num, String comp)
	{
		int len = right - left;
		if(len < num)
		{
			for(int i = left + 1; i <= right; i++)
			{
				for(int j = i; j > left && (tab.get(j).compareTo(tab.get(j-1)) < 0); j--)
				{
					comparesQuickDual++;
					swapS(tab, j, j-1);
				}
			}
			return;
		}
		int third = len / div;
		int m1 = left + third;
		int m2 = right - third;
		
		if(m1 <= left)m1 = left + 1;
		if(m2 >= right)m2 = right - 1;
		comparesQuickDual++;
		if(tab.get(m1).compareTo(tab.get(m2)) < 0)
		{
			swapS(tab, m1, left);
			swapS(tab, m2, right);
		}
		else
		{
			swapS(tab, m1, right);
			swapS(tab, m2, left);
		}
		String pivot1 = tab.get(left);
		String pivot2 = tab.get(right);
		
		int l = left + 1;
		int r = right -1;
		for(int k = l; k <= r; k++)
		{
			comparesQuickDual++;
			if(tab.get(k).compareTo(pivot1) < 0)
			{
				swapS(tab, k, l++);
			}
			else if(tab.get(k).compareTo(pivot2) > 0)
			{
				while(k < r && (tab.get(r).compareTo(pivot2) > 0) )
				{
					comparesQuickDual++;
					r--;
				}
				swapS(tab, k, r--);
				comparesQuickDual++;
				if(tab.get(k).compareTo(pivot1) < 0)
				{
					swapS(tab, k, l++);
				}
			}
			comparesQuickDual++;
		}
		int dist = r - l;
		if(dist < 13)
		{
			div++;
		}
		swapS(tab, l-1, left);
		swapS(tab, r+1, right);
		
		QuickInsertionSortStr(tab, left, l - 2, div, num, comp);
		QuickInsertionSortStr(tab, r + 2, right, div, num, comp);
		
		if(dist > len - 13 && pivot1 != pivot2)
		{
			for(int k = l; k < r; k++)
			{
				comparesQuickDual++;
				if(tab.get(k) == pivot1)
				{
					swapS(tab, k, l++);
				}
				else if(tab.get(k) == pivot2)
				{
					swapS(tab, k, r--);
					if(tab.get(k) == pivot1)
					{
						swapS(tab, k, l++);
					}
				}
				comparesQuickDual++;
			}
		}
		if(pivot1.compareTo(pivot2) < 0)
		{
			QuickInsertionSortStr(tab, l, r, div, num, comp);
		}
	}
	
	public static String QuickInsertionInit(ArrayList<Integer> tab, int num, String comp) throws Exception
	{
		comparesQuickDual = 0;
		swapsQuickDual = 0;
		startTimeQuickDual = System.nanoTime();
		int left = 0;
		int right = tab.size()-1;
		QuickInsertionSort(tab, left, right, 3, num, comp);
		endTimeQuickDual = System.nanoTime();
		long diff = endTimeQuickDual - startTimeQuickDual;
		double time = diff/1000000;
		String ans = comparesQuickDual + ";" + swapsQuickDual + ";" + diff + ";";
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
			for(int i = 0; i < tab.size(); i++)
			{
				System.err.print(tab.get(i) + " ");
			}
			throw new Exception();
		}
		else
		{
			return ans;
		}
	}
	
	public static String QuickInsertionInitStr(ArrayList<String> tab, int num, String comp) throws Exception
	{
		comparesQuickDual = 0;
		swapsQuickDual = 0;
		startTimeQuickDual = System.nanoTime();
		int left = 0;
		int right = tab.size()-1;
		QuickInsertionSortStr(tab, left, right, 3, num, comp);
		endTimeQuickDual = System.nanoTime();
		long diff = endTimeQuickDual - startTimeQuickDual;
		double time = diff/1000000;
		String ans = comparesQuickDual + ";" + swapsQuickDual + ";" + diff + ";";
		//System.err.println("comps: " + compares + " swaps: " + swaps + " time: " + time + "ms");
		boolean check = true;
		for(int i = 1; i < tab.size(); i++)
		{
			if(tab.get(i-1).compareTo(tab.get(i)) > 0)
			{
				check = false;
				break;
			}
		}
		if(!check)
		{
			for(int i = 0; i < tab.size(); i++)
			{
				System.err.print(tab.get(i) + " ");
			}
			throw new Exception();
		}
		else
		{
			return ans;
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
			QuickInit(tab, "<=");
		}
		else if(sortType.equals("merge"))
		{
			System.out.println("\n MergeSort");
			MegreInit(tab, "<=");
		}
		else if(sortType.equals("insert"))
		{
			System.out.println("\n Sort");
			InsertionSort(tab, "<=");
		}
		else if(sortType.equals("dual"))
		{
			System.out.println("\n DualPivotQuickSort");
			QuickDualInit(tab, "<=");
		}
		scanner.close();
	}
}
