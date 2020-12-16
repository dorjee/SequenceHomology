'''
Created on Apr 29, 2016 
@author: Dorjee Gyaltsen
'''

from homology_module import get_homolog

''' User input params '''
# threshold value (0-100)
threshold = 100
epitope_sequence = 'AVSGGLNTLVLRAVL'
protein_sequence = ('YIASRTSIAGRAWENTIVDLESDGKPQKLGTTGSNKSLQSAGFPAGLTYSQLMTLKDSMMQLDPS'
                    'AKTWIDIEGRPEDPVEIAIYQPMSGCYIHFFREPTDLKQFKQDAKYSHGIDVADLFPAQPGLTSA'
                    'VIEALPRNMVLTCQGSDDIKKLLDSQGRRDIKLIDISLNKAESRKFENAVWDQCKDLCHMHTGVV'
                    'VEKKKRGGKEEITPH')

''' | *brief*: Run the Python C extension code which generates a list of all possible
               peptides, residue start and end indices, maximum number of residue matches 
               and homology value in tuples.
'''
list_of_homolog_result = get_homolog(epitope_sequence, protein_sequence, threshold)

start = []; end = []; peptides = []; matches = []
''' Calculate the max homology '''
max_homology = max([tup[-1] for tup in list_of_homolog_result])

for _start, _end, _peptide, _matches, _homology in list_of_homolog_result:
    if _homology >= max_homology:
        start.append(int(_start))
        end.append(int(_end))
        peptides.append(_peptide)
        matches.append(_matches)
max_matches = max(matches)

''' | *brief*: Prints number of residue matches, homology value, and a list of tuple(predicted peptide, peptide start, peptide end) '''
print(max_matches, max_homology, list(zip(peptides, start, end)))
    
