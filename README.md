# SequenceHomology
Python C extension module to calculate homology between a peptide and a protein sequence. Code generates a list of all possible peptides, residue start and end indices, maximum number of residue matches and homology value in tuples.  


### Install/uninstall module in develop mode:
```bash
# install
python setup.py develop
# uninstall
python setup.py develop --uninstall
```

### Run the test:
```bash
python test_module.py
```

Above test contains following arguments:
```python
threshold = 100
epitope_sequence = 'AVSGGLNTLVLRAVL'
protein_sequence = (
    'YIASRTSIAGRAWENTIVDLESDGKPQKLGTTGSNKSLQSAGFPAGLTYSQLMTLKDSMMQLDPS'
    'AKTWIDIEGRPEDPVEIAIYQPMSGCYIHFFREPTDLKQFKQDAKYSHGIDVADLFPAQPGLTSA'
    'VIEALPRNMVLTCQGSDDIKKLLDSQGRRDIKLIDISLNKAESRKFENAVWDQCKDLCHMHTGVV'
    'VEKKKRGGKEEITPH'
)
```

### Expected output:
```bash
# output syntax:
# number_of_residue_matches, homology_value, [(predicted_peptide, peptide_start, peptide_end)]
4 26.666666666666668 [('AGRAWENTIVDLESD', 9, 23), ('PAQPGLTSAVIEALP', 122, 136), ('LTSAVIEALPRNMVL', 127, 141)]
```
