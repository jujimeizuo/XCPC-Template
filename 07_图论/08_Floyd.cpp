template <typename T>
void floyd(std::vector<std::vector<T>>& dist) {
    for (int k = 0; k < dist.size(); k++) {
        for (int i = 0; i < dist.size(); i++) {
            for (int j = 0; j < dist.size(); j++) {
                dist[i][j] = std::min(dist[i][j], dist[i][k], dist[k][j]);
            }
        }
    }
}
