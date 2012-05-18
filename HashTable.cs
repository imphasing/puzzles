using System;
using System.Collections.Generic;

// Simple hash table implementation

namespace HashTable
{
    class HashTable<TKey, TValue>
    {
        private int count;
        private int size;
        private List<KeyValuePair<TKey, TValue>>[] values;

        public HashTable()
        {
            this.count = 0;

            // initial size of 400
            this.size = 400;
            this.values = new List<KeyValuePair<TKey, TValue>>[this.size];
        }

        // Hash the key and find the array index for the backing store
        private int GetIndex(TKey key)
        {
            int index = Math.Abs(key.GetHashCode() % size);
            return index;
        }

        public void Add(TKey key, TValue value)
        {
            if (this.ContainsKey(key))
                throw new InvalidOperationException("Given key already exists in this HashTable");

            /* 
             * Resize the backing store if we've exceeded capacity, leave the old array just hanging around because
             * it's just an array of references that will be garbage collected.
	     * Probably inefficient to not be re-using the same KeyValuePairs when we resize, but meh, I'll fix it sometime. 
	     * This was a hack.
             */
            if (this.count == this.size)
            {
                int nextSize = size += size;
                var nextValues = new List<KeyValuePair<TKey, TValue>>[nextSize];

                var oldValues = this.values;
                this.values = nextValues;
                this.size = nextSize;
                this.count = 0;

                foreach (var bucket in oldValues)
                {
                    if (bucket != null)
                    {
                        foreach (var kvp in bucket)
                        {
                            this.Add(kvp.Key, kvp.Value);
                        }
                    }
                }
            }
 
            int index = this.GetIndex(key);

            if (values[index] == null)
                values[index] = new List<KeyValuePair<TKey, TValue>>();

            var bucketEntry = new KeyValuePair<TKey, TValue>(key, value);
            values[index].Add(bucketEntry);
            this.count++;
        }

        public TValue Get(TKey key)
        {
            int index = this.GetIndex(key);
            var bucket = values[index];

            // search through the bucket to find our actual kvp
            int bucketLocation = bucket.FindIndex(x => x.Key.Equals(key));

            if (bucketLocation == -1)
                throw new KeyNotFoundException("Given key was not found in this HashTable");

            return bucket[bucketLocation].Value;
        }

        public void Remove(TKey key)
        {
            int index = this.GetIndex(key);
            var bucket = values[index];

            // Find the key in the bucket and remove it
            int bucketLocation = bucket.FindIndex(x => x.Key.Equals(key));

            if (bucketLocation == -1)
                throw new KeyNotFoundException("Given key was not found in this HashTable");

            bucket.RemoveAt(bucketLocation);
        }

        public bool ContainsKey(TKey key)
        {
            int index = this.GetIndex(key);
            var bucket = values[index];

            // If the bucket isn't null and there's a kvp in the bucket, this key exists
            if (bucket != null && bucket.Count > 0)
            {
                int bucketLocation = bucket.FindIndex(x => x.Key.Equals(key));
                if (bucketLocation != -1)
                    return true;
            }

            return false;
        }
    }
}
