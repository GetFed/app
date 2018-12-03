export const camelToUpperCase = (str: string) => str.split(/(?=[A-Z])/).join(' ').toUpperCase();

export const camelToCapitalized = (str: string) =>
  str.split(/(?=[A-Z])/)
    .join(' ')
    .split(' ')
    .map(([firstLetter, ...tailLetters]) => `${firstLetter.toUpperCase()}${tailLetters.join('').toLowerCase()}`) 
    .join(' ');
