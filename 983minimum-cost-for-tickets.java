import java.util.Arrays;

// 最低票价
// 在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行
// 在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出
// 每一项是一个从 1 到 365 的整数
// 火车票有 三种不同的销售方式
// 一张 为期1天 的通行证售价为 costs[0] 美元
// 一张 为期7天 的通行证售价为 costs[1] 美元
// 一张 为期30天 的通行证售价为 costs[2] 美元
// 通行证允许数天无限制的旅行
// 例如，如果我们在第 2 天获得一张 为期 7 天 的通行证
// 那么我们可以连着旅行 7 天(第2~8天)
// 返回 你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费
// 测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/
public class Solution {
	public static int[] durations = { 1, 7, 30 };

	public static int mincostTickets(int[] days, int[] costs) {
		return f1(days, costs, 0);
	}
    //1 暴力 O(n2)
   public static int f1(int[] days, int[] costs,int i)
    {
        if(i==days.length)return 0;//后续没有了
        
        int res=Integer.MAX_VALUE;//初始化费用max
        for(int k= 0, j=i;k<3;k++)//1 7 30 3种
        {
            while(j<days.length && durations[k]+days[i]>days[j])
             {
                j++;//找下一个下标
             }   
             res=Math.min(res,costs[k]+f1(days,costs,j));
        }
    return res;
    }
    //2 记忆搜索 O(n)
    public static int mincostTickets(int[] days, int[] costs) {
        int[] dp=new int[days.length];
        for(int i=0;i<days.length;i++)dp[i]=Integer.MAX_VALUE;

		return f2(days, costs, 0,dp);
	}
    public static int f2(int[] days, int[] costs,int i,int[] dp)
    {
        if(i==days.length)return 0;
        if(dp[i]!=Integer.MAX_VALUE)return dp[i];
        int res=Integer.MAX_VALUE;
        for(int k=0,j=i;k<3;k++)
        {
            while(j<days.length && durations[k]+days[i]>days[j])
                j++;//找下一个下标
             res=Math.min(res,costs[k]+f2(days,costs,j,dp))
        }
        dp[i]=res;
        return res;
    }


}