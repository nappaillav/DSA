def maximalRectangle_1(matrix):
    """
    optimal approach O(n*m) - using stack and max histogram idea
    """


    def maxarea(heights):
        n = len(heights)
        if (n < 1):
            return 0
        stack = [-1]
        heights.append(0)
        max_area = 0
        for i, height in enumerate(heights):
            while (heights[stack[-1]] > height):
                h = heights[stack.pop()]
                width = i - stack[-1] - 1
                max_area = max(max_area, h * width)
            stack.append(i)
        heights.pop()
        return max_area


    m = len(matrix)
    if (m < 1):
        return 0
    n = len(matrix[0])
    if (n < 1):
        return 0
    heights = [0] * n
    out = 0

    for i in range(m):
        for j in range(n):
            if (matrix[i][j] == 0):
                heights[j] = 0
            else:
                heights[j] += 1
        out = max(maxarea(heights), out)

    return out

def maximalRectangle_2(matrix):
    """
    Optimal solution - O(m*n) using DP 
    Having an eye on either sides to compute the rectangular area
     
    """

    m = len(matrix)
    if (m < 1):
        return 0
    n = len(matrix[0])
    if (n < 1):
        return 0
    heights = [0] * n
    left, right = [0] * n, [n] * n
    max_a = 0

    for i in range(m):
        cur_left, cur_right = 0, n
        for j in range(n):
            if matrix[i][j]:
                heights[j] += 1
            else:
                heights[j] = 0

        for j in range(n):
            if matrix[i][j]:
                left[j] = max(left[j], cur_left)
            else:
                left[j] = 0
                cur_left = j+1

        j = n-1
        while(j >= 0):
            if matrix[i][j]:
                right[j] = min(right[j], cur_right)
            else:
                right[j] = n
                cur_right = j
            j -= 1

        for j in range(n):
            max_a = max(max_a, (right[j]-left[j])*heights[j])
        # print(left)
        # print(right)
        # print(heights)
        # print('-------------')

    return max_a

matrix_2 = [[1,0,1,0,0],[1,0,1,1,1],[1,1,1,1,1],[1,0,0,1,0]]
matrix_1 = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]

print(maximalRectangle_1(matrix_2))
print(maximalRectangle_2(matrix_2))
