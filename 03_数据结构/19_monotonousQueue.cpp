template <typename T>
struct monotonousQueue {
    std::vector<T> a;
    monotonousQueue(const std::vector<T>& init) : a(init) {}

    std::vector<T> Max(int k) {
        int n = (int) a.size();
        int head = 0, tail = -1;
        std::queue<int> que(n);
        std::vector<T> ans;
        for (int i = 0; i < n; i++) {
            while (head <= tail && a[que[tail]] <= a[i]) tail--;
            que[++tail] = i;
            while (que[head] + k <= i) head++;
            if (i >= k - 1) ans.push_back(a[que[head]]);
        }
        return ans;
    }

    std::vector<T> Min(int k) {
        int n = (int) a.size();
        int head = 0, tail = -1;
        std::queue<int> que(n);
        std::vector<T> ans;
        for (int i = 0; i < n; i++) {
            while (head <= tail && a[que[tail]] >= a[i]) tail--;
            que[++tail] = i;
            while (que[head] + k <= i) head++;
            if (i >= k - 1) ans.push_back(a[que[head]]);
        }
        return ans;
    }
};