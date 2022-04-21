make
./bin/main 100 100 100 100 | awk -F: '{print $1}' > nums1
seq 200 > nums2
cmp nums1 nums2
