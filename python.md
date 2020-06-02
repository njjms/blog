---
layout: page
title: Python
permalink: /python/
---

# Introduction

One of my recent hobbies with the quarantine has been doing interview-style programming questions in Python (I also watch other people do these questions too when I can't figure one out).
It's actually kind of fun, and a good way to kill time.
This page is intended to be a running document of questions that I find interesting and the solutions that I come up with, as well as any Python tips I come across.

I'm not a real programmer, but I do think it's valuble to have an understanding of data structures and algorithms as a statistician, especially if you spend a lot of time writing code.
While I know basic things like avoiding nested for loops, one thing I never really thought about was writing efficient code, especially thinking about time and space complexity.

The goal of these solutions should be to have as low a time complexity as possible (usually $O(N)$ -- maybe $O(1)$ or $O(n log n)$ for weird problems).

# Reversing a string

Here's a good intro problem and a couple ways to do it.
Given a string like 'abc', return 'cba'.

In Python, it's imporant to note that strings are **not mutable**.
Therefore, a common sense solution like:

{% highlight python %}
def reverse(x):
	output = ""
	for c in x:
		output = output + c	
{% endhighlight %}

Would actually be $O(N^2)$ in both space and time complexity since we have to create a new string with each iteration.
A slightly better way of thinking would be using a list:

{% highlight python %}
def reverse(x):
	output = []
	for c in range(len(x)-1):
		output.insert(0, c)

	return ''.join(output)
{% endhighlight %}

But this is still not great, since we are prepending data.
Anyone who has taken a data structures course knows that prepending to dynamic arrays is tricky since it involves shifting all existing elements by a single space, which is an $O(N)$ operation in itself.
So this solution is still $O(N^2)$.

This will be more efficient, using a deque from `collections`.
According to the docs: "Deques are a generalization of stacks and queues (the name is pronounced “deck” and is short for “double-ended queue”). Deques support thread-safe, memory efficient appends and pops from either side of the deque with approximately the same O(1) performance in either direction".

{% highlight python %}
from collections import deque
def reverse(x):
	d = deque('')
	for c in x:
		d.appendleft(c)

	return ''.join(d)
{% endhighlight %}

Another way that I saw [here](https://www.youtube.com/watch?v=cdCeU8DJvPM) which seemed pretty good is:

{% highlight python %}
def reverse(x):
	output_len = len(x)
	output = [None] * output_len
	output_index = output_len - 1
	for c in x:
		output[output_index] = c
		output_index -= 1

	return ''.join(output)
{% endhighlight %}

### Find missing element (full set vs. partial set)

This is a good question that came up in the above [video](https://www.youtube.com/watch?v=cdCeU8DJvPM).

Given two lists of unique integers where one list is a subset of the other minus one character, find the missing character.
We can do this with set operations, specifically difference.
This following code will run in linear time and this is the best case.
However, it will use additional space since we basically need to make a copy of my data.

{% highlight python %}
def find_missing(full_set, partial_set):
	missing_item = set(full_set) - set(partial_set)
	return list(missing_items)[0] # sets are not subscriptable
{% endhighlight %}

If we have spatial constraints and care less about the time complexity, we can sort the data first using an algorithm like heap sort which sorts in place.
Then we walk along the full set until we find an element that isn't in the partial sort.
This will have time complexity $O(n log n)$ since we have to sort the data first.

A really clever idea that was in the video is just to sum up each list (this of course requires that the input is numeric and there is only one missing element) and subtract them.
This would be a linear time operation to sum up the individual lists.
It would be almost constant space, but we have to be mindful that the sums might be very large and take up memory on their own so that it isn't constant space.

One thing from the video that I didn't understand use of the Python XOR function to create a function that takes constant space and linear time.

{% highlight python %}
def find_missing(full_set, partial_set):
	xor_sum = 0
	for num in full_set:
		xor_sum ^= num
	for num in partial_set:
		xor_sum ^= num

	return xor_sum
{% endhighlight %}

The trick here is understanding that if we start with 0 and then do XOR twice using some bits, we get 0 back again because the XORs undo each other.
Since the `partial_set` contains elements from the `full_set`, it will "undo" all the XOR operations from the full_set except for the one that is missing!
What a neat trick!

# containsCloseNums

This is a cool question I found [here](https://www.youtube.com/watch?v=NKZheZYbbu0).

Given an array of integers `nums` and an integer **k**, determine whether there are two distinct indices $i$ and $j$ in the array where `nums[i] == nums[j]` and the absolute difference between $i$ and $j$ is less than **k**.

The best way to do this is to use a hash map.

We move along `nums` once, making this function run in linear time.
For every integer we come across, we either add it to the hash map (the key will be the integer and the value will be the index) if it's not already there **or** check if the current value is within **k** of the index we are at in our loop.
If there is, then we return True.
If we finish the loop without returning, then we return False.

In Python, hash maps can be implemented using dictionaries so there's no need to actually have a hash function written out.

{% highlight python %}
def containsCloseNums(nums, k):
	check = {}
	for i in range(len(nums)):
		num = nums[i]
		if num in check:
			if abs(check[num] - i) <= k:
				return True
			else:
				check[num] = i
		else:
			check[num] = i
	else:
		return False
{% endhighlight %}

# firstNonRepeatingCharacter

We are given a string of lowercase letters as input.
Write a function that returns the first character we encounter that is not repeated in the string.
If there is no such character, we return "0".

Strategy:
+ use a dictionary to fill with counts of character, then loop through input.
+ then loop through dict.keys() and return the first one that has a value of 1
+ if you finish the loop, return "0"

{% highlight python %}
def firstNonRepeatingCharacter(input):
	counter = {}
	for c in input:
		if c in counter:
			counter[c] += 1
		else:
			counter[c] = 1

	for k in counter.keys():
		if counter[k] == 1:
			return k
	else:
		return "0"
	
{% endhighlight %}

This will be $O(2N)$ time complexity. 
The space complexity will be $O(N)$ as well since we need to create the hash map to store the counts.

Note that this solution cannot use `Counter` from `collections` since `Counter` dict subclasses are unordered.
We need the dict to be ordered for our second loop through to find the first non repeating character.

# firstDuplicate (value)

With an integer array as input, write a function that returns the first number that is repeated **twice** as we traverse the string from left to rigth.

If we get [2, 1, 3, 4, 1, 5, 2], as input should return 1.

Strategy:

+ Create a dictionary to store unique values that we see and iterate through the array
	+ We want to use a dictionary since we want constant look up time
+ If we encounter an integer that is already a key in the dictionary, then that integer is the first duplicate.

{% highlight python %}
def firstDuplicate(nums):
	seen = {}
	for num in nums:
		if num not in seen:
			seen[num] = 1
		elif num in seen:
			return num
		else:
			pass
	else:
		return -1
{% endhighlight %}

This solution has $O(N)$ complexity since we only have to iterate through the array once.
The space complexity will also be $O(N)$ since at most we will have to create a hash map with at most $N$ entries inside of it.

# firstDuplicate (index)

Just like the first problem ,but instead of returning the value of the first duplicate, return the index of the second occurence.

{% highlight python %}
def firstDuplicate(input):
	seen = {}
	for i in range(len(input)):
		if input[i] not in seen:
			seen[input[i]] = i
		elif input[i] in seen:
			return i
		else:
			pass
	else:
		return -1
{% endhighlight %}

**NOTE:** A set in python is actually a hash map with constant look up time, so we can use a set here as well!
Sets actually used to be implemented using optimized dictionaries on the backend.
This might save a little space complexity.

Assuming that the values must be between 1 and the length of the array, Nick White had a really clever solution to [this](https://www.youtube.com/watch?v=XSdr_O-XVRQ&t=23s) that uses less space complexity.

Strategy:

+ Treat the values in the array as indices to the array itself!
+ When we iterate through the array, we can mutate the integer located at the index of current value - 1, say make it negative
+ If we look up an integer that is already mutated, that means we've found our first duplicate

{% highlight python %}
def firstDuplicate(input):
	for num in nums:
		if nums[num - 1] < 0:
			return num
		else:
			nums[num - 1] = -1*nums[num - 1]
	else:
		return -1
{% endhighlight %}

This mutates the array, but it saves space complexity since we don't need to make a hash set now!

# sortedSquaredArray

Given a sorted array of integers, write a function that returns a sorted array containing the squares of those integers.

Just squaring each element and then sorting afterwards will work but it will be inefficient since the sorting will take $O(N log N)$.

Strategy:

+ We have to be careful of negative values. Since the array is sorted, compare the values at either end and that will be our largest value.
+ We then continue working inwards, adding values to a new sorted array as we go.

{% highlight python %}
def sortedSquaredArray(input):
	n = len(input)
	output = [None] * n
	start = 0
	end = n - 1
	for i in reversed(range(n)):
		if input[start]**2 >= input[end]**2:
			output[i] = input[start]**2
			start += 1
		else:
			output[i] = input[end]**2
			end -= 1
	return output
{% endhighlight %}

Since this solution only operates on an input element once, it is $O(N)$ time complexity with $O(N)$ space complexity to hold the output.

Note that we could have also used `range(0, n, -1)` instead of `reversed(range(n))`.

# maximumSumSubarray

Given an array of integers, find the maximum possible sum you can get from one of its contiguous subarrays.

This problem can be solved using Kadane's algorithm, detailed [here](https://hackernoon.com/kadanes-algorithm-explained-50316f4fd8a6):

+ Initialize the maximum sum to the first element of the array
+ Iterate through the array, keeping an iteration sum value. At each element, ask if it's better to add that element into the current subarray or start a new subarray on that element.
+ Compare the sum of that subarray to the current maximum sum and replace it if it is greater than
+ Once iteration is complete, we should have the greatest subarray.

{% highlight python %}
def maximumSumSubarray(nums):
	max_sum = nums[0]
	for i in range(1, len(nums)):
		current_sum = max(nums[i], maxsum+nums[i])
		max_sum = max(maxsum, currentsum)

	return max_sum
{% endhighlight %}

This solution iterates through the array once, so the time complexity is $O(N^2)$.
The space complexity will be $O(N^2)$.

# moveZeros

Given an array of integers, write a function to move all 0's to the end  of it while maintaining the relative order of the non-zero elements.
This needs to be done in place without making a copy of the array and we want to minimize the total number of operations.

As a former president would put it, **strategery**:

+ Iterate through the loop once, making the function $O(n)$. Keep a pointer to the "front" of the array.
+ Every time we encounter a non-zero value, we swap it with the value at the "front" and increase the "front" pointer by 1

{% highlight python %}
class Solution:
	def moveZeros(self, nums):
		front = 0
		for i in range(len(nums)):
			if nums[i] != 0:
				nums[front], nums[i] = nums[i], nums[front]
				front += 1
		return(nums)

nums = [1, 2, 0, 3, 4, 10, 5, 0, 0]
Solution().moveZeros(nums)
{% endhighlight %}

Returns `[1, 2, 3, 4, 10, 5, 0, 0, 0]` :)

Essentially what is happening is that the nonzero values get percolated in order to the front of the array, leaving all the 0s in the back.

# Find the kth largest element in a list

Given an N-array of numbers like `[3, 5, 2, 4, 6, 8]` and an integer $k \leq N$, return the kth largest element in the list.

Some initial ideas:

+ The easy solution would be to sort the list first and then just access the kth element. In Python, sorting is done via the [timsort](https://en.wikipedia.org/wiki/Timsort) algorithm which is $O(n logn)$ complexity at **worst** and $O(n)$ complexity at best.
+ An $O(n)$ average complexity solution would have to involve heaps, specifically a min heap where the smallest value is at the root of the tree. Once the heap is constructed, we remove from the heap k times to find our value.
	+ Building a heap is $O(n)$ complexity so this entire solution will be $O(n)$. In Python, we can use the `heapq` standard library.

{% highlight python %}
def findKthlargest(nums, k):
	from heapq import heapify, heappop
	numheap = heapify(nums)
	for _ in range(k-1):
		heappop(numheap)
	return(heapop(numheap))
{% endhighlight %}
