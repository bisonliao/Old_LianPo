package org.example;

import javax.swing.plaf.synth.SynthTextAreaUI;
import java.util.*;
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
    //这个版本真不好懂， 下面那个quickSort2应该好懂一点？
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
                // right的值当前小于pivot，交换。交换后right指示的位置可以认为空出来了
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
    // 划分函数：将数组划分为两部分，并返回 pivot 的最终位置
    static private  int partition(Object[] arr, int low, int high, Comparator<Object> comparator) {
        // 选择最右边的元素作为 pivot
        Object pivot = arr[high];
        int i = low - 1; // i 是小于 pivot 的元素的边界

        for (int j = low; j < high; j++) {
            // 如果当前元素小于 pivot
            if (comparator.compare(arr[j], pivot) < 0) {
                i++; // 扩展小于 pivot 的区域
                swap(arr, i, j); // 将当前元素交换到小于 pivot 的区域
            }
        }

        // 将 pivot 放到正确的位置
        swap(arr, i + 1, high);
        return i + 1; // 返回 pivot 的最终位置
    }
    //更好理解一点？
    static public void quickSort2(Object[] array, Comparator<Object> comparator) throws Exception
    {
        if (array == null || array.length <= 1)
        {
            return;
        }
        // 使用栈来模拟递归过程
        Stack<int[]> stack = new Stack<>();
        stack.push(new int[]{0, array.length - 1}); // 将整个数组的范围压入栈

        while (!stack.isEmpty()) {
            // 弹出栈顶范围
            int[] range = stack.pop();
            int low = range[0];
            int high = range[1];

            // 如果范围内的元素少于两个，无需排序
            if (low >= high) {
                continue;
            }

            // 对当前范围进行划分，找到 pivot 的最终位置
            int pivotIndex = partition(array, low, high, comparator);

            // 将划分后的左右子数组范围压入栈
            // 注意：先压入右边的范围，再压入左边的范围
            stack.push(new int[]{pivotIndex + 1, high}); // 右边子数组
            stack.push(new int[]{low, pivotIndex - 1});  // 左边子数组
        }
    }
    static class WinTreeNode
    {
       public Object data;
       public int from;
    };
    static private void voteInHeap(int parent, WinTreeNode[] heap,Comparator<Object> comparator )
    {
        int left = parent * 2 + 1;
        int right = parent * 2 + 2;
        if (heap[left] == null || heap[right] == null) {
            if (heap[left] == null)  // null是个哨兵，认为这个元素无穷大，来自于已经到头了的子数组
            {
                heap[parent] = heap[right];
            } else if (heap[right] == null) {
                heap[parent] = heap[left];
            }
        } else {
            int littleChild = left; // 左右孩子中较小的那个
            if (comparator.compare(heap[left].data, heap[right].data) > 0) {
                littleChild = right;
            }
            heap[parent] = heap[littleChild];
        }
    }
    // 模拟外部排序中的k路归并，使用我自己理解的一种败者树，类似最小堆进行归并
    static public void kMergeSort(Object[] array, Comparator<Object> comparator) throws Exception
    {
        //if (array.length < 100) {return;}

        final int k = 4; // k要选择为2的幂
        int subArrayLen = array.length / k;
        if ( (array.length % k) != 0) {subArrayLen++;}

        // split array into k sub arrays and sort them
        List<Object[]> subArrayArray = new ArrayList<Object[]>();
        int count = 0;
        for (int i = 0; i < k; ++i)
        {
            int tmpLen = subArrayLen;
            if (i+1 == k) {tmpLen = array.length - (k-1)*subArrayLen;}

            Object[] oneSubArray = new Object[tmpLen];
            for (int j = 0; j < tmpLen; ++j)
            {
                oneSubArray[j] = array[count++];
            }
            insertSort(oneSubArray, comparator);
            subArrayArray.add(oneSubArray);
        }


        //先装填k个叶子节点，并初始化最小堆
        final int heapSize = k + k -1;
        WinTreeNode[] heap = new WinTreeNode[heapSize];
        int [] subArrayIndex = new int[k];
        for (int i = 0; i < k; ++i)
        {
            subArrayIndex[i] = 0;
            WinTreeNode node = new WinTreeNode();
            node.data = subArrayArray.get(i)[ subArrayIndex[i]++ ];
            node.from = i;
            heap[heapSize-k + i] = node;
        }
        // 初始化的方法就是：从下标最大的一个父亲开始，逐步减一，检查所有父亲及其左右孩子，是否符合最大堆规则
        for (int i = heap.length - k - 1; i >= 0; i--)
        {
            voteInHeap(i, heap, comparator);
        }
        // 一个一个元素开始归并
        //太复杂： 一方面要吧非叶子节点中每个元素来自哪个子数组要记住，一方面还要考虑个别子数组到头了该怎么处理，例如设置一个无穷大的哨兵？
        for (int i = 0; i < array.length; ++i)
        {
            array[i] = heap[0].data;

            int from = heap[0].from;
            if (subArrayIndex[from] < subArrayArray.get(from).length) // more data to reduce
            {
                WinTreeNode node = new WinTreeNode();
                node.data = subArrayArray.get(from)[ subArrayIndex[from]++ ];
                node.from = from;
                heap[heap.length-k+from] = node;
            }
            else // no data to reduce in sub array #from
            {
                heap[heap.length-k+from] = null;
            }

            int parent = ((heap.length-k+from)-1)/2;
            while (parent >= 0) {
                voteInHeap(parent, heap, comparator);
                if (parent > 0) {
                    parent = (parent - 1) / 2; // continue to check
                }
                else
                {
                    parent = -1;
                }

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
    private static void insertSort4shell(Object[] array, Comparator<Object> comparator, int start, int gap)
    {
        //从第二个元素开始，每一个元素，都拿出来和前面的已经排好序的部分数组相比，找到适合插入的位置
        for (int i = gap+start; i < array.length; i += gap)
        {
            int j;

            int targetPosition;
            for (j = i - gap; j >= start; j -= gap) {
                if (comparator.compare(array[i], array[j]) >= 0) {
                    break;
                }
            }
            if (j < start) // array[i]比前面任何数都小，那么它将被插入到位置0
            {
                targetPosition = start;
            } else {
                targetPosition = j + gap;//否则他被插入到j的下一个元素
            }

            // 挨个往后移动一个位置
            Object tmp = array[i];
            for (int k = i; k > targetPosition; k-= gap)
            {
                array[k] = array[k-gap];
            }
            array[targetPosition] = tmp;
        }
    }

    //tmd我还是要自己实现一下希尔排序
    public static void shellSortByBison(Object[] array, Comparator<Object> comparator)
    {
        int n = array.length;
        for (int gap = n / 2; gap > 0; gap = gap / 2)
        {
            for (int i = 0; i < gap; ++i) // gap确定后，数组就被分成了gap个子数组，对每个子数组做插入排序
            {
                insertSort4shell(array, comparator, i, gap);
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


        final int arrlen = 27;
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
                    array[j] = Integer.valueOf(r.nextInt() % 10);
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
                    shellSortByBison(array, new MyComparator());
                    break;
                case 9:
                    kMergeSort(array, new MyComparator());
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
