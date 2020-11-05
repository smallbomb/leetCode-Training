// https://leetcode.com/problems/find-mode-in-binary-search-tree/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct Record {
    int val;
    int times;
    struct Record *next;
};

void add_record(struct Record** record, int val) {
    if (!*record) {
        *record = calloc(1,sizeof(struct Record));
        (*record)->val = val;
        (*record)->times = 1;
    }
    else if ((*record)->val == val) {
        (*record)->times += 1;
    }
    else {
        add_record(&(*record)->next, val);
    }

}

int max_size(struct Record* record, int times) {
    int size = 0;
    struct Record* head = record;
    for (; head; head=head->next) {
        if (times == head->times)
            size += 1;
    }
    return size;
}

int max_times(struct Record* record) {
    int times = 0;
    struct Record* head = record;
    for (; head; head=head->next) {
        if (times < head->times)
            times = head->times;
    }
    return times;
}


void findMode_ex(struct TreeNode* root, struct Record** record) {
    add_record(record, root->val);
    if (root->left) {
        findMode_ex(root->left, record);
    }
    if (root->right) {
        findMode_ex(root->right, record);
    }
}

void add_modes(struct Record* record, int maxTimes, int *modes) {
    int times = 0;
    struct Record* head = record;
    int i=0;
    for (; head; head=head->next) {
        if (maxTimes == head->times) {
            modes[i] = head->val;
            i++;
        }
    }
}

void free_record(struct Record** record) {
    if (!*record) return;
    free_record(&(*record)->next);
    free(*record);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMode(struct TreeNode* root, int* returnSize){
    struct Record *record = NULL;
    if (root) {
        findMode_ex(root, &record);
    }
    int maxTimes = max_times(record);
    int size = max_size(record, maxTimes);
    *returnSize = size;
    int *modes = malloc(size * sizeof(int));
    add_modes(record, maxTimes, modes);
    free_record(&record);
    return modes;
}