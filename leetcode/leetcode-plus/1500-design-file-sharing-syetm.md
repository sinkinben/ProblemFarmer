## Design File Sharing System

Leetcode: [1500. Design a File Sharing System](https://leetcode-cn.com/problems/design-a-file-sharing-system/)

We will use a file-sharing system to share a very large file which consists of `m` small chunks with IDs from 1 to `m`.

When users join the system, the system should assign a unique ID to them. The unique ID should be used once for each user, but when a user leaves the system, the ID can be reused again.

Users can request a certain chunk of the file, the system should return a list of IDs of all the users who own this chunk. If the user receives a non-empty list of IDs, they receive the requested chunk successfully.

Implement the `FileSharing` class:

- `FileSharing(int m)` Initializes the object with a file of `m` chunks.
- `int join(int[] ownedChunks)`: A new user joined the system owning some chunks of the file, the system should assign an id to the user which is the **smallest positive integer** not taken by any other user. Return the assigned id.
- `void leave(int userID)`: The user with `userID` will leave the system, you cannot take file chunks from them anymore.
- `int[] request(int userID, int chunkID)`: The user `userID` requested the file chunk with `chunkID`. Return a list of the IDs of all users that own this chunk sorted in ascending order.

**Constraints:**

- `1 <= m <= 105`
- `0 <= ownedChunks.length <= min(100, m)`
- `1 <= ownedChunks[i] <= m`
- Values of `ownedChunks` are unique.
- `1 <= chunkID <= m`
- `userID` is guaranteed to be a user in the system if you assign the IDs correctly.
- At most `1e4` calls will be made to join, `leave` and `request`.
- Each call to `leave` will have a matching call for `join`.

**Follow-up:**

- What happens if the system identifies the user by their IP address instead of their unique ID and users disconnect and connect from the system with the same IP?
- If the users in the system join and leave the system frequently without requesting any chunks, will your solution still be efficient?
- If all users join the system one time, request all files, and then leave, will your solution still be efficient?
- If the system will be used to share `n` files where the `i`-th file consists of `m[i]`, what are the changes you have to make?

```cpp
class FileSharing {
public:
    priority_queue<int, vector<int>, greater<int>> idQueue;
    unordered_map<int, unordered_set<int>> userToChunk, chunkToUser;
    int maxId;
    const int NR_CHUNKS;
    FileSharing(int m) : maxId(1), NR_CHUNKS(m) {}
    
    int join(vector<int> ownedChunks) {
        int uid = -1;
        if (idQueue.empty())
            idQueue.emplace(maxId++);
        uid = idQueue.top(), idQueue.pop();
        for (int chunk : ownedChunks) {
            userToChunk[uid].emplace(chunk);
            chunkToUser[chunk].emplace(uid);
        }
        return uid;
    }
    
    void leave(int userID) {
        for (int chunk : userToChunk[userID])
            chunkToUser[chunk].erase(userID);
        userToChunk.erase(userID);
        idQueue.emplace(userID);
    }
    
    vector<int> request(int userID, int chunkID) {
        vector<int> res(chunkToUser[chunkID].begin(), chunkToUser[chunkID].end());
        sort(begin(res), end(res));
        if (!res.empty()) {
            chunkToUser[chunkID].emplace(userID);
            userToChunk[userID].emplace(chunkID);
        }
        return res;
    }
};
```

