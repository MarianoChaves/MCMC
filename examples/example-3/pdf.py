import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


df = pd.read_csv("samples.csv")


df = df[['x','y','z']]
sns.set_theme(style="dark")
g = sns.PairGrid(df, diag_sharey=False)
g.map_upper(sns.scatterplot, s=5, alpha = 0.1, color = 'red')
g.map_lower(sns.kdeplot, fill=True, levels=[0.01, 0.05, 0.1, 0.42, 1], cmap = 'Reds')
g.map_diag(sns.histplot, kde=True, color = 'red')
plt.savefig("pdf.png", dpi=300)
plt.show()
