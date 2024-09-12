package org.example;

import javax.swing.plaf.synth.SynthTextAreaUI;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Queue;
import java.util.Random;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class MySort {
    // 在数组的闭区间[start, end]内查找 target 的合适的位置
    static public int binarySearch(Object[] array, int start, int end, Object target, Comparator<Object> comparator)
    {
        int compResult = comparator.compare(target, array[start]);
        if (compResult < 0) { return start;}
        if (compResult == 0) { return start+1;}
        if (comparator.compare(target, array[end]) >= 0) {return end+1;}

        while (start + 4 < end) {
            int position = (start + end) / 2;
            compResult = comparator.compare(target, array[position]);
            if (compResult < 0) {
                end = position;
            }
            else if (compResult > 0)
            {
                start = position;
            }
            else
            {
                return position+1;
            }
        }
        int j;
        for (j = end; j >= start; j--)
        {
            if (comparator.compare(target, array[j]) >= 0)
            {
                break;
            }
        }
        if (j < start)
        {
            return start;
        }
        else
        {
            return j+1;
        }


    }

    static public void insertSort(Object[] array, Comparator<Object> comparator)
    {
        //从第二个元素开始，每一个元素，都拿出来和前面的已经排好序的部分数组相比，找到适合插入的位置
        for (int i = 1; i < array.length; ++i)
        {
            int j;

            int targetPosition;
            if (i > 32) // 如果前面要查找位置的数组比较长，就折半查找，否则直接顺序比较
            {
                targetPosition = binarySearch(array, 0, i-1, array[i], comparator);
            }
            else {
                for (j = i - 1; j >= 0; --j) {
                    if (comparator.compare(array[i], array[j]) >= 0) {
                        break;
                    }
                }
                if (j < 0) // array[i]比前面任何数都小，那么它将被插入到位置0
                {
                    targetPosition = 0;
                } else {
                    targetPosition = j + 1;//否则他被插入到j的下一个元素
                }
            }
            // 挨个往后移动一个位置
            Object tmp = array[i];
            for (int k = i; k > targetPosition; --k)
            {
                array[k] = array[k-1];
            }
            array[targetPosition] = tmp;
        }
    }

    static public void bubbleSort(Object[] array, Comparator<Object> comparator)
    {
        for (int k = 0; k < array.length;++k) {
            boolean swapFlag = false;
            for (int i = 0; i < array.length - 1 - k; ++i) {
                if (comparator.compare(array[i], array[i + 1]) > 0) {
                    swap(array, i, i+1);
                    swapFlag = true;
                }
            }
            if (!swapFlag) // 这是个优化项，如果后面都没有进行过一次交换，说明已经是有序的了
            {
                break;
            }
        }
    }
    static public void selectSort(Object[] array, Comparator<Object> comparator)
    {
        for (int i = 0; i < array.length-1; ++i)
        {
            int minIndex = i;
            for (int j = i+1; j < array.length; ++j)
            {
                if (comparator.compare(array[j], array[minIndex]) < 0)
                {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                swap(array,i, minIndex);
            }
        }
    }
    static private void swap(Object[] array, int i, int j)
    {
        Object tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
    static public void mergeSort(Object[] array, Comparator<Object> comparator)
    {
        BlockingQueue< ArrayList<Object> > subArrays = new LinkedBlockingQueue< ArrayList<Object> >();

        // 长度为n的数组，被认为是n个已经排好序的子数组
        for (int i = 0; i < array.length; ++i)
        {
            ArrayList<Object> subArr = new ArrayList<Object>(); //一个排好序的子数组
            subArr.add(array[i]);
            subArrays.add(subArr);
        }
        while (subArrays.size() > 1)
        {
            // 拿出两个来归并
            ArrayList<Object> arr1 = subArrays.remove();
            ArrayList<Object> arr2 = subArrays.remove();
            ArrayList<Object> subArr = new ArrayList<Object>(); //结果子数组

            int i, j;
            for (i = 0, j = 0; i < arr1.size() && j < arr2.size(); )
            {
                int cmp = comparator.compare(arr1.get(i), arr2.get(j));
                if (cmp < 0)
                {
                    subArr.add(arr1.get(i));
                    i++;
                }
                else if (cmp == 0)
                {
                    subArr.add(arr1.get(i));
                    subArr.add(arr2.get(j));
                    i++;
                    j++;
                }
                else
                {
                    subArr.add(arr2.get(j));
                    j++;
                }
            }
            for (; i < arr1.size(); i++) {
                subArr.add(arr1.get(i));
            }

            for (; j < arr2.size(); j++) {
                subArr.add(arr2.get(j));
            }

            subArrays.add(subArr);

        }
        ArrayList<Object> subArr = subArrays.remove();
        for (int i = 0; i < subArr.size();++i)
        {
            array[i] = subArr.get(i);
        }

    }

    static  public void quickSort(Object[] array, Comparator<Object> comparator) throws Exception
    {
        BlockingQueue< ArrayList<Integer> > jobs = new LinkedBlockingQueue< ArrayList<Integer> >();
        ArrayList<Integer> job = new ArrayList<Integer>();
        job.add(Integer.valueOf(0));
        job.add(Integer.valueOf(array.length-1));
        jobs.add(job);
        while (!jobs.isEmpty())
        {
            job = jobs.remove();
            int start = job.get(0).intValue();
            int end = job.get(1).intValue();
            if (end <= start) {continue;}
            Object pivot = array[end]; // end这个位置可以认为空出来了
            int left = start;
            int right = end;

            while (left < right)
            {
                while (comparator.compare(array[left], pivot) <= 0 && left < right)
                {
                    left++;
                }
                // left的值当前大于pivot, 交换。交换后left指示的位置可以认为空出来了。
                swap(array, left, right);

                while (comparator.compare(array[right], pivot) >= 0 && left < right)
                {
                    right--;
                }
                // right的值当前大于pivot，交换。交换后right指示的位置可以认为空出来了
                swap(array, left, right);
            }
            if (left != right) throw new Exception("quickSort Error!");
            array[left] = pivot;

            if (left-1 > start)
            {
                job = new ArrayList<Integer>();
                job.add(Integer.valueOf(start));
                job.add(Integer.valueOf(left-1));
                jobs.add(job);

            }
            if (end > left+1)
            {
                job = new ArrayList<Integer>();
                job.add(Integer.valueOf(left+1));
                job.add(Integer.valueOf(end));
                jobs.add(job);

            }

        }

    }
    static public void radixSort(Object[] array, Comparator<Object> comparator) // 我这里只能排序正整数
    {
        final int RNUM = 10;
        Object[] buckets = new Object[RNUM]; //基数为10
        for (int i = 0; i < RNUM; i++)
        {
            buckets[i] = new ArrayList<Object>();
        }
        boolean needMoreRound = true;
        int round = 0;
        int maxValue = 10;
        while (needMoreRound)
        {
            needMoreRound = false;

            for (int i = 0; i < array.length; ++i)
            {
                if (comparator.compare(array[i], Integer.valueOf(maxValue)) >= 0)
                {
                    needMoreRound = true;
                }

                int subscript = ((Integer)array[i]).intValue();
                for (int j = 0; j < round; ++j)
                {
                    subscript = subscript / 10;
                }
                subscript = subscript % 10;

                ((ArrayList<Object>)buckets[subscript]).add(array[i]);
            }
            int index = 0;
            for (int i = 0; i < RNUM; ++i)
            {
                ArrayList<Object> bucket = (ArrayList<Object>)buckets[i];
                for (int j = 0; j < bucket.size(); ++j)
                {
                    array[index++] = bucket.get(j);
                }
                bucket.clear();
            }
            round++;
            maxValue = maxValue * 10;
        }
    }

    static public void heapSort(Object[] array, Comparator<Object> comparator)
    {
        if (array.length < 2)
        {
            return;
        }
        // 构造最大堆，使其符合最大堆的规则
        // 方法就是：从最大的一个父亲开始，逐步减一，检查所有父亲及其左右孩子，是否符合最大堆规则
        for (int i = (array.length-1 -1) / 2; i >= 0; i--)
        {
            int parent = i;
            while(parent != -1)
            {
                int left = parent * 2 + 1;
                int right = parent * 2 + 2;
                int bigChild = -1; // 左右孩子中较大的那个
                if (left < array.length) { bigChild = left;}
                if (right < array.length)
                {
                    if (comparator.compare(array[bigChild], array[right]) < 0)
                    {
                        bigChild = right;
                    }
                }
                if (bigChild != -1 && comparator.compare(array[parent], array[bigChild]) < 0)
                {
                    swap(array, bigChild, parent);

                    parent = bigChild; // 继续调整
                }
                else
                {
                    parent = -1; // 一路往下已经调整到位了，子树没有被破坏规则
                }

            }
        }
        //不断的从最大堆里删除最大元素，其实是把它放在数组的后部
        // 下标从 0 到i 是一个最大堆，0位置是最大元素的位置，从堆里删除最大元素，把它放到 位置i，原来位置i的元素放到位置0
        // 又开始修正最大堆，这一次是从0 到i-1是一个最大堆。如此反复直到大小为1
        for (int i = array.length-1; i > 0; i--)
        {
            {
                swap(array, i, 0);
            }
            int heapSize = i;

            //规则已经被打破，修复最大堆，要一直捅到叶子节点
            int parent = 0;
            while (parent != -1)
            {

                int left = parent * 2 + 1;
                int right = parent * 2 + 2;
                int bigChild = -1; // 左右孩子中较大的那个
                if (left < heapSize) {
                    bigChild = left;
                }
                if (right < heapSize) {
                    if (comparator.compare(array[bigChild], array[right]) < 0) {
                        bigChild = right;
                    }
                }
                if (bigChild != -1 && comparator.compare(array[parent], array[bigChild]) < 0) {
                    swap(array, bigChild, parent);

                    parent = bigChild;// 继续往下修复
                }
                else
                {
                    parent = -1;//子树没有被破坏，不需要往下了
                }

            }

        }

    }
    //希尔排序真他妈的不好理解，我写不出来也看不明白，下面的代码是chatGPT写的。
    public static void shellSort(Object[] array, Comparator<Object> comparator) {
        int n = array.length;
        // 选择初始增量（一般选择 n/2）
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // 使用增量对数组进行排序
            for (int i = gap; i < n; i++) {
                // 记录当前元素
                Object temp = array[i];
                int j = i;
                // 插入排序的过程
                while (j >= gap && comparator.compare(array[j - gap], temp) > 0) {
                    array[j] = array[j - gap];
                    j -= gap;
                }
                array[j] = temp;
            }
        }
    }


    public static void testSort(int kind) throws Exception
    {
        class MyComparator implements Comparator<Object>
        {
            public int compare(Object a, Object b)
            {
                Integer aa = (Integer) a;
                Integer bb = (Integer) b;
                return aa.intValue() - bb.intValue();
            }
        };


        final int arrlen = 51;
        final int round = 20;
        Random r = new Random();
        Integer[] array = new Integer[arrlen];
        for (int i = 0; i < round; ++i)
        {
            for (int j = 0; j < arrlen; ++j)
            {
                if (i == 0)
                {
                    array[j] = j;
                   // array[j] = Integer.valueOf(r.nextInt() % 10);
                }
                else if (i == 1)
                {
                    array[j] = j / 2;
                }
                else {
                    array[j] = Integer.valueOf(Math.abs(r.nextInt()) % 1000);
                }
            }

            switch (kind) {
                case 1:
                    insertSort(array, new MyComparator());
                    break;
                case 2:
                    bubbleSort(array, new MyComparator());
                    break;
                case 3:
                    selectSort(array, new MyComparator());
                    break;
                case 4:
                    heapSort(array, new MyComparator());
                    break;
                case 5:
                    quickSort(array, new MyComparator());
                    break;
                case 6:
                    mergeSort(array, new MyComparator());
                    break;
                case 7:
                    radixSort(array, new MyComparator());
                    break;
                case 8:
                    shellSort(array, new MyComparator());
                    break;
                default:
                    bubbleSort(array, new MyComparator());
                    break;
            }

            for (int j = 0; j < arrlen-1; ++j)
            {
                if (i < 10 ) {System.out.print(" "+array[j]);}

                if (array[j] > array[j+1])
                {
                    throw new Exception("error!"+array[j] +" "+ array[j+1]);
                }



            }
            if (i < 10) {System.out.println(" "+array[arrlen-1]);}
        }
    }
}
