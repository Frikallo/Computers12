#include <bits/stdc++.h>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> boxes_l, boxes_w, boxes_h;
    for ( int i=0; i < n; ++i ) {
        int l0, w0, h0;
        std::cin >> l0 >> w0 >> h0;
        boxes_l.push_back(l0);
        boxes_w.push_back(w0);
        boxes_h.push_back(h0);
    }
    int m;
    std::cin >> m;
    std::vector<int> parcels_l, parcels_w, parcels_h;
    for ( int i=0; i < m; ++i ) {
        int l1, w1, h1;
        std::cin >> l1 >> w1 >> h1;
        parcels_l.push_back(l1);
        parcels_w.push_back(w1);
        parcels_h.push_back(h1);
    }
    std::vector<int> boxes;
    for ( int i=0; i < n; ++i ) {
        int l0 = boxes_l[i];
        int w0 = boxes_w[i];
        int h0 = boxes_h[i];
        boxes.push_back(l0*w0*h0);
    }

    // Find smallest box that can fit each parcel, given that they may be rotated
    for ( int i=0; i < m; ++i ) {
        int l1 = parcels_l[i];
        int w1 = parcels_w[i];
        int h1 = parcels_h[i];
        int min_box = -1;
        for ( int j=0; j < n; ++j ) {
            int l0 = boxes_l[j];
            int w0 = boxes_w[j];
            int h0 = boxes_h[j];
            if ( (l1 <= l0 && w1 <= w0 && h1 <= h0) ||
                 (l1 <= l0 && w1 <= h0 && h1 <= w0) ||
                 (l1 <= w0 && w1 <= l0 && h1 <= h0) ||
                 (l1 <= w0 && w1 <= h0 && h1 <= l0) ||
                 (l1 <= h0 && w1 <= l0 && h1 <= w0) ||
                 (l1 <= h0 && w1 <= w0 && h1 <= l0) ) {
                if ( min_box == -1 || boxes[j] < boxes[min_box] ) {
                    min_box = j;
                }
            }
        }
        if ( min_box == -1 ) {
            std::cout << "Item does not fit." << std::endl;
        } else {
            std::cout << boxes[min_box] << std::endl;
        }
    }
    return 0;
}