using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

/*
 * Example Usage:
 * 
 * List<string> urls = new List<string> { "/img/something.jpg", "/img/nothing.jpg", "/static/res.html", "/script/test.js" };
 * 
 * // enter more powerful cache servers more than once, 127.0.0.3 in this case is 3 times as powerful, 
 * // meaning it should get 3 times the load as the others.
 * List<string> caches = new List<string> { "127.0.0.2", "127.0.0.3-1", "127.0.0.3-2", "127.0.0.3-3", "127.0.0.4" };
 *
 * // each cache is entered 150 times, between 100 and 200 seems to be the butter zone for even distribution
 * ConsistentHash<string, string> cacheFinder = new ConsistentHash<string, string>(urls, caches, 150, new MD5CryptoServiceProvider());
 *
 * string cacheToUse = cacheFinder.Get("/img/something.jpg");
 *
 */

namespace ConsistentHash
{
    class ConsistentHash<TKey, TValue>
    {
        private HashAlgorithm hashAlgorithm;
        private int repsPerValue;

        private Dictionary<TKey, long> distributedKeys;
        private Dictionary<long, TValue> distributedValues;

        public ConsistentHash(List<TKey> keys, List<TValue> values, int repsPerValue, HashAlgorithm hashAlgorithm)
        {
            this.distributedKeys = new Dictionary<TKey, long>();
            this.distributedValues = new Dictionary<long, TValue>();
            this.hashAlgorithm = hashAlgorithm;
            this.repsPerValue = repsPerValue;

            foreach (TKey key in keys)
            {
                this.AddKey(key);
            }

            foreach (TValue value in values)
            {
                this.AddValue(value);
            }
        }

        public TValue Get(TKey key)
        {
            long keyIndex = distributedKeys[key];

            List<long> sortedValues = distributedValues.Keys.ToList();
            sortedValues.Sort();

            if (keyIndex > sortedValues.Last())
            {
                return distributedValues[sortedValues.First()];
            }

            long clockwiseNext = sortedValues.Where(x => x > keyIndex).First();

            return distributedValues[clockwiseNext];
        }

        public void AddKey(TKey key)
        {
            byte[] hashed = hashAlgorithm.ComputeHash(Encoding.UTF8.GetBytes(key.ToString()));

            // take the top 8 bytes and make random enough number
            long top8 = BitConverter.ToInt64(hashed, 0);
            distributedKeys.Add(key, top8);
        }

        public void AddValue(TValue value)
        {
            if (this.repsPerValue > 0)
            {
                for (int i = 0; i < this.repsPerValue; i++)
                {
                    byte[] hashed = hashAlgorithm.ComputeHash(Encoding.UTF8.GetBytes(value.ToString() + i.ToString()));

                    // take the top 8 bytes and make random enough number
                    distributedValues.Add(BitConverter.ToInt64(hashed, 0), value);
                }
            }
            else
            {
                byte[] hashed = hashAlgorithm.ComputeHash(Encoding.UTF8.GetBytes(value.ToString()));
                distributedValues.Add(BitConverter.ToInt64(hashed, 0), value);
            }
        }

        public void RemoveKey(TKey key)
        {
            distributedKeys.Remove(key);
        }

        public void RemoveValue(TValue value)
        {
            if (this.repsPerValue > 0)
            {
                for (int i = 0; i < this.repsPerValue; i++)
                {
                    byte[] hashed = hashAlgorithm.ComputeHash(Encoding.UTF8.GetBytes(value.ToString() + i.ToString()));
                    distributedValues.Remove(BitConverter.ToInt64(hashed, 0));
                }
            }
            else
            {
                byte[] hashed = hashAlgorithm.ComputeHash(Encoding.UTF8.GetBytes(value.ToString()));
                distributedValues.Remove(BitConverter.ToInt64(hashed, 0));
            }
        }
    }
}
