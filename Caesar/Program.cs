using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace Caesar {
    class Program {
        static void Main(string[] args) {
            string alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
            
            byte[] streamIn = File.ReadAllBytes("input.txt");
            string fileData = Encoding.UTF8.GetString(streamIn);
            string inputInLower = fileData.ToLower();

            Dictionary<char, int> freqAnalysis = new Dictionary<char, int>();
            foreach (var letter in alphabet)
                freqAnalysis.Add(letter, 0);

            foreach(var symbol in inputInLower)
                if (!Char.IsPunctuation(symbol) && !Char.IsWhiteSpace(symbol))
                    freqAnalysis[symbol]++;

            int maxValue = freqAnalysis.Values.Max();
            char mostFrequent = freqAnalysis.First(x => x.Value == maxValue).Key;

            int offset = alphabet.IndexOf('о') - alphabet.IndexOf(mostFrequent);
            if (offset < 0) offset += 33;

            string shiftedAlphabet = "";
            shiftedAlphabet += alphabet.Substring(offset);
            shiftedAlphabet += alphabet.Substring(0, offset);

            string result = "";
            for(int i = 0; i < inputInLower.Length; ++i) {
                if (!Char.IsPunctuation(inputInLower[i]) && !Char.IsWhiteSpace(inputInLower[i])) {
                    int posOfLetter = alphabet.IndexOf(inputInLower[i]);
                    if (Char.IsUpper(fileData[i])) result += Char.ToUpper(shiftedAlphabet[posOfLetter]);
                    else result += shiftedAlphabet[posOfLetter];
                }
                else result += inputInLower[i];
            }

            byte[] b = Encoding.Default.GetBytes(result);
            File.WriteAllBytes("output.txt", b);
        }
    }
}
