import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


df = pd.read_csv("samples.csv")

if(True):
    walker_id = df.walker.drop_duplicates().array


    fig, ax = plt.subplots(3,1,constrained_layout=True)    
    for walker in walker_id:
        df_aux = df.loc[df["walker"]==walker]
        size = len(df_aux["x"].index)
        x = np.linspace(0,size,size)
        ax[0].plot(x, df_aux["y"], alpha=0.3, color = 'black')
        ax[1].plot(x, df_aux["x"], alpha=0.3, color = 'black')
        ax[2].plot(x, df_aux["z"], alpha=0.3, color = 'black')
    ax[0].set_xlabel("y")
    ax[1].set_xlabel("x")
    ax[2].set_xlabel("z")
    plt.show()


if(True):
    df = df[['x','y','z']]
    sns.set_theme(style="dark")
    g = sns.PairGrid(df, diag_sharey=False)
    g.map_upper(sns.scatterplot, s=5, alpha = 0.1, color = 'red')
    g.map_lower(sns.kdeplot, fill=True, levels=[0.01, 0.05, 0.1, 0.42, 1], cmap = 'Reds')
    g.map_diag(sns.histplot, kde=True, color = 'red')
    plt.show()
