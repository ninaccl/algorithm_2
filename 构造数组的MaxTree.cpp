// 构造数组的MaxTree
// 【题目】
// 定义二叉树节点如下：
// public class Node
// {
//     public int value;
//     public Node left;
//     public Node right;
//
//     public Node(int data)
//     {
//         this.value = data;
//     }
// }
// 一个数组的MaxTree定义如下。
// 数组必须没有重复元素。
// MaxTree时一棵二叉树，数组中的每一个值对应于一个二叉树节点。
// 包括MaxTree树在内且在其中的每一棵子树上，值最大的节点都是树的头。
// 没有重复元素的数组arr，写出生成这个数组的MaxTree的函数，要求如果数组长度为N，则时间和空间复杂度为O(N)
//
// 【解决方法】 时间复杂度O(N*M)
// 单调栈找左边右边最近最大值
// 若只有单边最大，则直接挂在下面
// 若没有大的，则为头节点
// 若有两边更大的，则挂在它们中间的小的那个下面

// 关键：单调栈

