## Design Twitter

Leetcode: https://leetcode.com/problems/design-twitter/

Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the `10` most recent tweets in the user's news feed.

Implement the `Twitter` class:

- `Twitter()` Initializes your twitter object.
- `void postTweet(int userId, int tweetId)` Composes a new tweet with ID `tweetId` by the user `userId`. Each call to this function will be made with a unique `tweetId`.
- `List<Integer> getNewsFeed(int userId)` Retrieves the `10` most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be **ordered from most recent to least recent**.
- `void follow(int followerId, int followeeId)` The user with ID `followerId` started following the user with ID `followeeId`.
- `void unfollow(int followerId, int followeeId)` The user with ID `followerId` started unfollowing the user with ID `followeeId`.

**Brute Force Solution**

- User a grid `map<int, map<int, int>>` to record the follower-followee relations.
- Use `vector<{userId, tweetId}>` to store tweets.
- Fast, but low scalability. It will scan all tweets.

```cpp
class Twitter {
public:
    unordered_map<int, unordered_map<int, bool>> followMap;
    vector<pair<int, int>> tweets;

    /* O(1) */
    void postTweet(int userId, int tweetId) { tweets.emplace_back(userId, tweetId); }
    /* O(n) where n denote the number of tweets */
    vector<int> getNewsFeed(int userId)
    {
        vector<int> res;
        for (auto i = tweets.rbegin(); i != tweets.rend(); ++i)
        {
            if (userId == i->first || followMap[userId][i->first])
            {
                res.emplace_back(i->second);
                if (res.size() == 10) break;
            }
        }
        return res;
    }
    /* O(1) */
    void follow(int followerId, int followeeId) { followMap[followerId][followeeId] = 1; }
    /* O(1) */
    void unfollow(int followerId, int followeeId) { followMap[followerId][followeeId] = 0; }
};

```

<br/>

**Object Oriented Solution**

Consider the real product environment, there will be database tables to store the users and tweets. Therefore, we design such data structures:

```cpp
struct User
{
    unordered_set<int> followees;  // the followee list
    list<int> recentTweets;        // the recent 10 tweets
};
struct Tweet
{
    int timestamp;
    bool operator < (const Tweet &t) const { return timestamp > t.timestamp; }
};
unordered_map<int, User> userTable;
unordered_map<int, Tweet> tweetTable;
```

And in this problem, **we do not need to store all the tweets**. Only store the recent 10 tweets for each user.

```cpp
class Twitter {
public:
    unordered_map<int, User> userTable;
    unordered_map<int, Tweet> tweetTable;
    int timestamp = 0;
    /* O(1) */
    void postTweet(int userId, int tweetId) {
        tweetTable[tweetId] = Tweet{timestamp++};
        userTable[userId].recentTweets.emplace_back(tweetId);

        if (userTable[userId].recentTweets.size() > 10)
            userTable[userId].recentTweets.pop_front();
    }
    /* O(nlogn) where n = followee.length */
    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        
        /* the user themself */
        for (int tid : userTable[userId].recentTweets)
            res.emplace_back(tid);
        
        /* the user's followees */
        auto &followees = userTable[userId].followees;
        for (int uid : followees)
            for (int tid : userTable[uid].recentTweets)
                res.emplace_back(tid);
        
        sort(begin(res), end(res), [this](int x, int y) {
           return tweetTable[x].timestamp > tweetTable[y].timestamp;
        });
        
        return vector<int>(res.begin(), res.begin() + min(10, int(res.size())));
    }
    /* O(1) */
    void follow(int followerId, int followeeId) {
        userTable[followerId].followees.emplace(followeeId);
    }
    /* O(1) */
    void unfollow(int followerId, int followeeId) {
        userTable[followerId].followees.erase(followeeId);
    }
};
```

