import java.math.*;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        BigInteger n, x;
        String s;

        //定义"two"为BigInteger类，值为2
        BigInteger two = new BigInteger("2");

        n = in.nextBigInteger();

        //toString()方法返回该对象的字符串表示,保存在s中
        s = n.toString();

        //x为BigInteger类，值为 截取字符串开头到s.length()/2 + 1位置的子串 并转化成BigInteger类
        x = new BigInteger(s.substring(0, s.length()/2 + 1));

        //当x * x > n时,
        //x = (x + (n/x)) / 2
        while(x.multiply(x).compareTo(n) > 0)
            x = x.add(n.divide(x)).divide(two);
    }
}

