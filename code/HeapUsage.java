package org.example;
import java.util.*;
import java.lang.*;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class HeapUsage {
    static private void swap(Object[] array, int i, int j) {
        Object tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
    static public Object getMedian(Object[] array, Comparator<Object> comparator)
    {
        if (array.length < 5)
        {
            heapSort(array, comparator);
            return array[array.length / 2];
        }
        Object[] maxHeap = new Object[array.length / 2]; //负责前面一半元素的大顶堆
        Object[] minHeap = new Object[array.length - maxHeap.length]; // 负责后面一半元素的小顶堆
        int i, j;
        for (i = 0; i < maxHeap.length; ++i)
        {
            maxHeap[i] = array[i];
        }
        for (j = 0; i < array.length; ++i, ++j)
        {
            minHeap[j] = array[i];
        }
        heapify(maxHeap, comparator, false);
        heapify(minHeap, comparator, true);
        while (! (comparator.compare(maxHeap[0], minHeap[0]) <= 0 )) // 当前面最大的都比后面最小的小，说明前面部分的都比后面部分小，否则就交换堆顶
        {
            Object tmp = maxHeap[0];
            maxHeap[0] = minHeap[0];
            minHeap[0] = tmp;

            reheapifyTopDown(maxHeap, comparator, false, maxHeap.length);
            reheapifyTopDown(minHeap, comparator, true, minHeap.length);
        }
        return minHeap[0];
    }
    public static void reheapifyTopDown(Object[] array, Comparator<Object> comparator, boolean isMinHeap, int heapSize)
    {

        //规则已经被打破，修复最小堆，要一直捅到叶子节点
        int parent = 0;
        if (isMinHeap) {
            while (parent != -1) {

                int left = parent * 2 + 1;
                int right = parent * 2 + 2;
                int smallChild = -1; // 左右孩子中较大的那个
                if (left < heapSize) {
                    smallChild = left;
                }
                if (right < heapSize) {
                    if (comparator.compare(array[smallChild], array[right]) > 0) {
                        smallChild = right;
                    }
                }
                if (smallChild != -1 && comparator.compare(array[parent], array[smallChild]) > 0) {
                    swap(array, smallChild, parent);

                    parent = smallChild;// 继续往下修复
                } else {
                    parent = -1;//子树没有被破坏，不需要往下了
                }

            }
        }
        else
        {
            //规则已经被打破，修复最大堆，要一直捅到叶子节点
            while (parent != -1) {

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
                } else {
                    parent = -1;//子树没有被破坏，不需要往下了
                }

            }
        }
    }
    static public void heapify(Object[] array, Comparator<Object> comparator, boolean isMinHeap )
    {
        if (!isMinHeap) {
            // 构造最大堆，使其符合最大堆的规则
            // 方法就是：从最大的一个父亲开始，逐步减一，检查所有父亲及其左右孩子，是否符合最大堆规则
            for (int i = (array.length - 1 - 1) / 2; i >= 0; i--) {
                int parent = i;
                while (parent != -1) {
                    int left = parent * 2 + 1;
                    int right = parent * 2 + 2;
                    int bigChild = -1; // 左右孩子中较大的那个
                    if (left < array.length) {
                        bigChild = left;
                    }
                    if (right < array.length) {
                        if (comparator.compare(array[bigChild], array[right]) < 0) {
                            bigChild = right;
                        }
                    }
                    if (bigChild != -1 && comparator.compare(array[parent], array[bigChild]) < 0) {
                        swap(array, bigChild, parent);

                        parent = bigChild; // 继续调整
                    } else {
                        parent = -1; // 一路往下已经调整到位了，子树没有被破坏规则
                    }

                }
            }
        }
        else
        {
            // 构最小堆，使其符合最小堆的规则
            // 方法就是：从最大的一个父亲开始，逐步减一，检查所有父亲及其左右孩子，是否符合最小堆规则
            for (int i = (array.length - 1 - 1) / 2; i >= 0; i--) {
                int parent = i;
                while (parent != -1) {
                    int left = parent * 2 + 1;
                    int right = parent * 2 + 2;
                    int smallChild = -1; // 左右孩子中较小的那个
                    if (left < array.length) {
                        smallChild = left;
                    }
                    if (right < array.length) {
                        if (comparator.compare(array[smallChild], array[right]) > 0) {
                            smallChild = right;
                        }
                    }
                    if (smallChild != -1 && comparator.compare(array[parent], array[smallChild]) > 0) {
                        swap(array, smallChild, parent);

                        parent = smallChild; // 继续调整
                    } else {
                        parent = -1; // 一路往下已经调整到位了，子树没有被破坏规则
                    }

                }
            }
        }
    }

    static public void heapSort(Object[] array, Comparator<Object> comparator) {
        if (array.length < 2) {
            return;
        }
        boolean isMinHeap = false;
        heapify(array, comparator, isMinHeap);
        //不断的从最大堆里删除最大元素，其实是把它放在数组的后部
        // 下标从 0 到i 是一个最大堆，0位置是最大元素的位置，从堆里删除最大元素，把它放到 位置i，原来位置i的元素放到位置0
        // 又开始修正最大堆，这一次是从0 到i-1是一个最大堆。如此反复直到大小为1
        for (int i = array.length - 1; i > 0; i--) {
            {
                swap(array, i, 0);
            }
            int heapSize = i;

            reheapifyTopDown(array, comparator, false, heapSize);
        }

    }
    public static Object topK(Object[] array, Comparator<Object> comparator, int k )
    {
        if (k < 1 || k > array.length) { return null;}
        Object[] heap = new Object[k]; // 一个最小堆，保存可能的最大的k个元素，堆顶是k个最大元素里最小的
        int i, j;
        for (i = 0; i < k; ++i)
        {
            heap[i] = array[i];
        }
        boolean minHeap = true;
        heapify(heap, comparator, minHeap);
        for (i = k; i < array.length; ++i)
        {
            if (comparator.compare(array[i], heap[0]) > 0) // 元素比最小堆里最小的元素还要大，说明它是在top k里可能排得上号的
            {
                heap[0] = array[i];
                reheapifyTopDown(heap, comparator, true, heap.length);
            }
        }
        return heap[0];
    }

    public static void testSort() throws Exception {
        class MyComparator implements Comparator<Object> {
            public int compare(Object a, Object b) {
                Integer aa = (Integer) a;
                Integer bb = (Integer) b;
                return aa.intValue() - bb.intValue();
            }
        }
        ;


        final int arrlen = 27;
        final int round = 20;
        Random r = new Random();
        Integer[] array = new Integer[arrlen];
        for (int i = 0; i < round; ++i) {
            for (int j = 0; j < arrlen; ++j) {
                if (i == 0) {
                    array[j] = j;
                    array[j] = Integer.valueOf(r.nextInt() % 10);
                } else if (i == 1) {
                    array[j] = j / 2;
                } else {
                    array[j] = Integer.valueOf(Math.abs(r.nextInt()) % 1000);
                }
            }


            heapSort(array, new MyComparator());

            for (int j = 0; j < arrlen - 1; ++j) {
                if (i < 10) {
                    System.out.print(" " + array[j]);
                }

                if (array[j] > array[j + 1]) {
                    throw new Exception("error!" + array[j] + " " + array[j + 1]);
                }


            }
            if (i < 10) {
                System.out.println(" " + array[arrlen - 1]);
            }
        }

    }
    public static void testTopK() throws Exception {
        class MyComparator implements Comparator<Object> {
            public int compare(Object a, Object b) {
                Integer aa = (Integer) a;
                Integer bb = (Integer) b;
                return aa.intValue() - bb.intValue();
            }
        }
        ;


        final int arrlen = 27;
        final int round = 20;
        Random r = new Random();
        Integer[] array = new Integer[arrlen];
        for (int i = 0; i < round; ++i) {
            for (int j = 0; j < arrlen; ++j) {
                if (i == 0) {
                    array[j] = j;
                    array[j] = Integer.valueOf(r.nextInt() % 10);
                } else if (i == 1) {
                    array[j] = j / 2;
                } else {
                    array[j] = Integer.valueOf(Math.abs(r.nextInt()) % 1000);
                }
            }
            Object top7 = topK(array,  new MyComparator(), 7);
            heapSort(array, new MyComparator());

            for (int j = 0; j < arrlen - 1; ++j) {
                if (i < 10) {
                    System.out.print(" " + array[j]);
                }

                if (array[j] > array[j + 1]) {
                    throw new Exception("error!" + array[j] + " " + array[j + 1]);
                }


            }
            if (i < 10) {
                System.out.println(" " + array[arrlen - 1]);

            }

            if (top7!= null)
            {
                System.out.println("top7="+top7 + ", "+array[arrlen - 7]);
            }

        }

    }
    public static void testGetMedian() throws Exception {
        class MyComparator implements Comparator<Object> {
            public int compare(Object a, Object b) {
                Integer aa = (Integer) a;
                Integer bb = (Integer) b;
                return aa.intValue() - bb.intValue();
            }
        }
        ;


        final int arrlen = 27; // 搞成奇数
        final int round = 20;
        Random r = new Random();
        Integer[] array = new Integer[arrlen];
        for (int i = 0; i < round; ++i) {
            for (int j = 0; j < arrlen; ++j) {
                if (i == 0) {
                    array[j] = j;
                    array[j] = Integer.valueOf(r.nextInt() % 10);
                } else if (i == 1) {
                    array[j] = j / 2;
                } else {
                    array[j] = Integer.valueOf(Math.abs(r.nextInt()) % 1000);
                }
            }
            Object median = getMedian(array,  new MyComparator());
            heapSort(array, new MyComparator());

            for (int j = 0; j < arrlen - 1; ++j) {
                if (i < 10) {
                    System.out.print(" " + array[j]);
                }

                if (array[j] > array[j + 1]) {
                    throw new Exception("error!" + array[j] + " " + array[j + 1]);
                }


            }
            if (i < 10) {
                System.out.println(" " + array[arrlen - 1]);

            }

            System.out.println("median="+median + ", "+array[arrlen/2]);


        }

    }
    public static void main(String[] args) throws Exception
    {
        testGetMedian();
    }
}
