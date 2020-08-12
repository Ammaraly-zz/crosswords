//This file contains the script to scrape words from: http://www.scrabble.org.au/words/fours.htm
var myString = document.activeElement.textContent.toString()
regex = /[A-Z][A-Z][A-Z][A-Z]/gm;
myString.match(regex).join('\n')