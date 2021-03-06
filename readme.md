<!--Markdown En HTML. Utilisez une lecteur de markdown de votre IDE, ou votre navigateur Internet, pour afficher le contenu formatté-->
<style>
    code{
        font-family: 'Courier New', Courier, monospace;
    }
    .key{
        color:black;
        background-color: lightgray;
    }
    .instruction{
        color:green;
        background-color: rgb(49, 49, 49);
    }
    .file{
        font-weight: bold;
        color:slategray;
    }
    table, th, tr, td{
        border: solid 2pt;
        border-color:rgb(49, 49, 49);
    }
    th{
        color:black;
        font-weight: bold;
        background-color: grey;
    }
    td{
        font-style: italic;
    }
</style>
<h1>BESTIOLES</h1>
<p> Le sujet du projet est dans Sujet.pdf </p>

<p style="color:red">GROUPE 4</p>
<i> Mehdi Hajjam - Wadia Ferjani - Anass Benfathallah - Julien Bénard</i>

<h2>INSTALLER</h2>
<ul>
    <li>
        Utiliser le Makefile: <code>:$ make all</code>
    </li>
    <li>
        Lancer le programme avec <code>:$ ./main</code>
    </li>
    <li>
        Si vous voulez, nettoyez les objets <code>:$ make clean</code>
    </li>
    <li>
        Le Paramétrage de la simulation se fait via le fichier <b class="file">"InputData.txt"</b>.
    </li>
    <li>
        La récupération des résultats de la simulation se fait dans le fichier <b class="file">"Output.csv"</b>.
    </li>   
    <li>
        Pour Désinstaller <code>:$ make clean-all</code>
    </li>
</ul>
<h2>CONTROLES EN COURS DE SIMULATION</h2>
<ul>
    <li><b class="key">spacebar</b> (dans le programme de simulation) Pour mettre la simulation en pause, ou remettre en route </li>
    <li><b class="key">k</b> (dans le programme de simulation) Pour activer l'utilitaire de suppression de créatures. Il faut alors ensuite écrire dans la console le numéro de la Bestiole à tuer. Un faux numéro annule la commande. La commande met automatiquement la simulation en pause. Réactivez avec <b class="key">spacebar</b></li>
    <li><b class="key">Esc</b> (dans le programme de simulation)Interrompre définitivement la Simulation</li>
    <li><b class="key">r</b> (dans le programme de simulation) Afficher le contenu de la simulation</li>
    <li><b class="key">c</b> (dans le programme de simulation) Compter les Bestioles dans l'Aquarium</li>
    <li><b class="key">n</b> (dans le programme de simulation) Ajouter des Bestioles dans la simulation, en utilisant, dans la console, la syntaxe de paramétrage de simulation, et en remplaçant la proportion par le nombre de bestioles à ajouter. Une erreur annule la commande. La commande met automatiquement la simulation en pause. Réactivez avec <b class="key">spacebar</b></li>
</ul>
<h2>SYNTAXE DE PARAMETRAGE DE LA SIMULATION</h2>
<ul>
    <li>Le fichier à modifier est <b class="file">"InputData.txt"</b> pour le paramétrage initial de la simulation. Les résultats sont stockés dans <b class="file">"Output.csv"</b></li>
    <li>Les sauts de ligne sont requis entre chaque instruction et on ne peut pas enchaîner plusieurs instructions sur une même ligne. Il est recommandé de ne pas écrire à la suite d'instructions, sur la même ligne, cela pouvant avoir des effets inattendus, allant d'aucun effet à un arrêt de la lecture des instructions.</li>
    <li>Il est impossible de couper une instruction et de la répartir sur plusieurs lignes. Il est possible Néanmoins de sauter autant de lignes que l'on souhaite entre chaque instruction.</li>
    <li>Les indentations sont prohibées, ainsi que les caractères d'espacement à la fin des lignes.</li>
    <li>Tout paramétrage, qu'il soit réalisé avec le fichier d'entrée ou les commandes de la console, doit s'achever par une instruction <code class="instruction">STOP</code> (ou <code class="instruction">Stop</code>).</li>
    <li>De manière générale, répéter une instruction ou redéfinir une valeur est possible, et la simulation sera réalisée avec la dernière redéfinition de la valeur</li>
    <li>Le fichier d'instruction doit commencer par la définition des paramètres de simulation. Le bloc des paramètres de simulation commence par l'instruction <code class="instruction">Simulation</code> sur une ligne. Il est suivi (ou non) par plusieurs lignes attribuant des valeurs personnalisées aux propriétés de la simulation.</li>
    <li>Chaque propriété peut voir sa valeur redéfinie à l'aide du mot <code class="instruction">Propriété</code> suivie du <strong style="text-decoration: underline;">Nom de la propriété</strong> (voir liste des propriétés plus bas) et de la valeur attribuée à la propriété. Cette redéfinition est facultative et les valeurs par défaut seront appliquées si l'instruction de redéfinition n'est pas donnée. (voir tableau)</li>
    <li>Il est ensuite nécessaire de définir les bestioles présentes. Cela est fait via le bloc "Bestioles", qui doit commencer par l'instruction, sur une ligne <code class="instruction">Bestioles</code>.</li>
    <li>Dans le bloc "Bestioles" peuvent être définies les différents types de Bestioles. La définition d'un type de Bestiole se fait via l'instruction <code class="instruction">Type [Nom de type (facultatif)] p: [valeur de la proportion]</code>. Le nom de type sert à identifier le type de bestioles dans les retours de la console, mais également sur les statistiques. Il est facultatif, de même que la proportion et son préfixe <code class="instruction">p:</code>. Indiquer la proportion est néanmoins fortement recommandé, ou la valeur par défaut de 1 sera donnée, et pourra causer un sureffectif. Il est également recommandé que la somme des proportions fasse 1, ou l'effectif réel ne sera pas celui demandé.</li>
    <li>Après la définition d'un type suivent obligatoirement les différentes caractéristiques de ce type (membres et comportements). Celles-ci sont déclarées sur les lignes suivantes de cette manière <code class="instruction">[nom de caractéristique] [paramètre] [valeur] [paramètre] [valeur] [paramètre] [valeur]</code> où le <strong style="text-decoration: underline;">Nom de la caractéristique</strong> (voir liste des caractéristique plus bas) est le nom de l'organe ou du comportement, et les différents paramètres et leurs valeurs correspondent aux paramètre de cette caractéristique. Une bestiole doit obligatoirement avoir toutes ses caractéristiques spécifiées, sinon elle n'en aura pas. Les paramètres de chaque caractéristiques doivent tous recevoir une valeur, sinon la caractéristique ne sera pas appliquée. Seul le comportement peut être ommis, auquel cas il est défini comme "Dumb" (Aller en ligne droite).</li>
    <li>Lors de l'utilisation de la commande <b class="key">n</b>, seule l'instruction de type, les définitions de caractéristiques, et l'instruction <code class="instruction">STOP</code> sont nécessaires.
</ul>
<h2>TABLEAU DES PROPRIETES</h2>
<table>
    <tr>
        <th>Nom de propriété</th>
        <th>Type</th>
        <th>Description</th>
        <th>Valeur Min</th>
        <th>Valeur Max</th>
        <th>Par défaut</th>
    </tr>
    <tr>
        <th>POPULATION</th>
        <td>int</td>
        <td>Population Moyenne visée (si les proportions sont bien renseignées)</td>
        <td>0</td>
        <td>300</td>
        <td>64</td>
    </tr>
    <tr>
        <th>LIFE</th>
        <td>int</td>
        <td>Espérance de vie en époques d'une Bestiole</td>
        <td>20</td>
        <td>2000</td>
        <td>660</td>
    </tr>
    <tr>
        <th>WINDOW_H</th>
        <td>int</td>
        <td>Hauteur en Pixels de la fenêtre</td>
        <td>400</td>
        <td>+Inf</td>
        <td>600</td>
    </tr>
    <tr>
        <th>WINDOW_W</th>
        <td>int</td>
        <td>Largeur en Pixels de la fenêtre</td>
        <td>400</td>
        <td>+Inf</td>
        <td>800</td>
    </tr>
    <tr>
        <th>AFF_SIZE</th>
        <td>double</td>
        <td>Taille d'affichage des bestioles à l'écran</td>
        <td>3.1</td>
        <td>+Inf</td>
        <td>8.0</td>
    </tr>
    <tr>
        <th>MULTIPLE_CHANGE_RATE</th>
        <td>int</td>
        <td>Nombre moyen d'époques de la simulation avant qu'un comportement multiple ne change</td>
        <td>10</td>
        <td>+Inf</td>
        <td>300</td>
    </tr>
    <tr>
        <th>MAX_VITESSE</th>
        <td>double</td>
        <td>Vitesse Maximale d'une Bestiole sans membre supplémentaire</td>
        <td>2.0</td>
        <td>10.0</td>
        <td>6.5</td>
    </tr>
    <tr>
        <th>MAX_PHI</th>
        <td>double</td>
        <td>Valeur Max du paramètre Phi des Camouflages</td>
        <td>MIN_PHI, 0</td>
        <td>+Inf</td>
        <td>1.0</td>
    </tr>
    <tr>
        <th>MIN_PHI</th>
        <td>double</td>
        <td>Valeur Min du paramètre Phi des Camouflages</td>
        <td>0</td>
        <td>MAX_PHI</td>
        <td>0</td>
    </tr>
    <tr>
        <th>MAX_DELTA_O</th>
        <td>double</td>
        <td>Valeur Max du paramètre Delta des Oreilles</td>
        <td>MIN_DELTA_O, 0</td>
        <td>+Inf</td>
        <td>39.6</td>
    </tr>
    <tr>
        <th>MIN_DELTA_O</th>
        <td>double</td>
        <td>Valeur Min du paramètre Delta des Oreilles</td>
        <td>0</td>
        <td>MAX_DELTA_O</td>
        <td>11.5</td>
    </tr>
    <tr>
        <th>MAX_GAMMA_O</th>
        <td>double</td>
        <td>Valeur Max du paramètre Gamma des Oreilles</td>
        <td>MIN_GAMMA_O, 0</td>
        <td>+Inf</td>
        <td>1.0</td>
    </tr>
    <tr>
        <th>MIN_GAMMA_O</th>
        <td>double</td>
        <td>Valeur Min du paramètre Gamma des Oreilles</td>
        <td>0</td>
        <td>MAX_GAMMA_O</td>
        <td>0</td>
    </tr>
    <tr>
        <th>MAX_DELTA_Y</th>
        <td>double</td>
        <td>Valeur Max du paramètre Delta des Yeux</td>
        <td>MIN_DELTA_Y, 0</td>
        <td>+Inf</td>
        <td>68.8</td>
    </tr>
    <tr>
        <th>MIN_DELTA_Y</th>
        <td>double</td>
        <td>Valeur Min du paramètre Delta des Yeux</td>
        <td>0</td>
        <td>MAX_DELTA_Y</td>
        <td>16.5</td>
    </tr>
    <tr>
        <th>MAX_GAMMA_Y</th>
        <td>double</td>
        <td>Valeur Max du paramètre Gamma des Yeux</td>
        <td>MIN_GAMMA_Y, 0</td>
        <td>+Inf</td>
        <td>1.0</td>
    </tr>
    <tr>
        <th>MIN_GAMMA_Y</th>
        <td>double</td>
        <td>Valeur Min du paramètre Gamma des Yeux</td>
        <td>0</td>
        <td>MAX_GAMMA_Y</td>
        <td>0</td>
    </tr>
    <tr>
        <th>MAX_ALPHA</th>
        <td>double</td>
        <td>Valeur Max du paramètre Alpha des Yeux</td>
        <td>MIN_ALPHA, 0</td>
        <td>2*PI</td>
        <td>4.59</td>
    </tr>
    <tr>
        <th>MIN_ALPHA</th>
        <td>double</td>
        <td>Valeur Min du paramètre Alpha des Yeux</td>
        <td>0</td>
        <td>MAX_ALPHA, 2*PI</td>
        <td>0.31</td>
    </tr>
    <tr>
        <th>MAX_OMEGA</th>
        <td>double</td>
        <td>Valeur Max du paramètre Omega de la Carapace</td>
        <td>1.0</td>
        <td>10.0</td>
        <td>4.5</td>
    </tr>
    <tr>
        <th>MAX_ETA</th>
        <td>double</td>
        <td>Valeur Max du paramètre Eta de la Carapace</td>
        <td>1.0</td>
        <td>5.5</td>
        <td>2.9</td>
    </tr>
    <tr>
        <th>MAX_NU</th>
        <td>double</td>
        <td>Valeur Max du paramètre Nu de la Nageoire</td>
        <td>1.0</td>
        <td>5.5</td>
        <td>2.7</td>
    </tr>
    <tr>
        <th>CLONE_RATE</th>
        <td>double</td>
        <td>Probabilité de clonage d'une créature à chaque époque de la simulation</td>
        <td>0</td>
        <td>0.1</td>
        <td>0.0008</td>
    </tr>
    <tr>
        <th>GENERATION_RATE</th>
        <td>double</td>
        <td>Facteur de réapparition des Bestioles (selon les proportions initiales)</td>
        <td>0</td>
        <td>10.0</td>
        <td>3.26</td>
    </tr>
    <tr>
        <th>SURVIVE_COLLISION</th>
        <td>double</td>
        <td>Probabilité qu'une Bestiole survive à une collision avec une autre bestiole</td>
        <td>0</td>
        <td>1.0</td>
        <td>0.88</td>
    </tr>
    <tr>
        <th>PROPORTION_CHANGE</th>
        <td>double</td>
        <td>Pourcentage maximal de modification de sa vitesse pour une bestiole (sans collision). Non-Inertie</td>
        <td>0</td>
        <td>1.0</td>
        <td>0.207</td>
    </tr>
</table>
<h2>TABLEAU DES CARACTERISTIQUES</h2>
<table>
    <tr>
    <th>Caractéristique</th>
    <th>Effet</th>
    <th>Paramètres</th>
    </tr>
    <tr>
    <th>Camouflages</th>
    <td>Réduit la visibilité de la Bestiole</td>
    <td><table><tr><th>Phi</th><td>Facteur de Camouflage</td><td>[MIN_PHI; MAX_PHI]</td></tr></table></td>
    </tr>
    <tr>
    <th>Carapace</th>
    <td>Réduit la probabilité de mort de Bestiole lors des chocs. Ralentit la Bestiole.</td>
    <td><table><tr><th>Omega</th><td>Facteur de Protection</td><td>[1.0; MAX_OMEGA]</td></tr><tr><th>Eta</th><td>Facteur de Ralentissement</td><td>[1.0; MAX_ETA]</td></tr></table></td>
    </tr>
    <tr>
    <th>Nageoire</th>
    <td>Augmente la vitesse de la bestiole.</td>
    <td><table><tr><th>Nu</th><td>Coefficient d'accélération</td><td>[1.0; MAX_NU]</td></tr></table></td>
    </tr>
    <tr>
    <th>Oreilles</th>
    <td>Permet à la bestiole de percevoir les autres bestioles dans un rayon autour d'elle.</td>
    <td><table><tr><th>Delta</th><td>Distance maximale de perception</td><td>[MIN_DELTA_O; MAX_DELTA_O]</td></tr><tr><th>Gamma</th><td>Efficacité de la perception</td><td>[MIN_GAMMA_O; MAX_GAMMA_O]</td></tr></table></td>
    </tr>
    <tr>
    <th>Yeux</th>
    <td>Permet à la bestiole de percevoir les autres bestioles dans un secteur angulaire devant elle.</td>
    <td><table><tr><th>Delta</th><td>Distance maximale de perception</td><td>[MIN_DELTA_Y; MAX_DELTA_Y]</td></tr><tr><th>Gamma</th><td>Efficacité de la perception</td><td>[MIN_GAMMA_Y; MAX_GAMMA_Y]</td></tr><tr><th>Alpha</th><td>Angle du secteur de perception</td><td>[MIN_ALPHA; MAX_ALPHA]</td></tr></table></td>
    </tr>
    <tr>
    <th>Comportement</th>
    <td>Détermine les actions de la Bestiole:</td>
    <td><table><tr><th>Multiple</th><td>La bestiole change de comportement régulièrement parmi les autres comportements</td><td>N°-1</td></tr><tr><th>Peureuse</th><td>La bestiole fuit dès qu'elle détecte trop de bestioles proches</td><td>N°0</td></tr><tr><th>Kamikaze</th><td>La bestiole ralentit puis attaque à toute vitesse la bestiole la plus proche</td><td>N°1</td></tr><tr><th>Prévoyante</th><td>La bestiole tourne à gauche ou à droite pour éviter les collisions</td><td>N°2</td></tr><tr><th>Grégaire</th><td>La bestiole s'adapte à la vitesse de ses voisines.</td><td>N°3</td></tr></table></td>
    </tr>
</table>
<h2>EXEMPLE DE PARAMETRAGE</h2>

<code>
Simulation<br>
Propriété POPULATION 80<br>
Propriété LIFE 680<br>
Propriété MAX_PHI 1.0<br>
Propriété WINDOW_H 800<br>
<br>
Propriété MAX_ETA 5.4<br>
<br>
Bestioles<br>
<br>
Type Troupeau p: 0.25<br>
<br>
Carapace eta 2.6 omega 3.8<br>
Camouflages phi 0.1<br>
Oreilles delta 26.5 gamma 0.3<br>
<br>
Comportement Gregaire<br>
<br>
<br>
<br>
Type Thinker p: 0.25<br>
Oreilles gamma 0.9 delta 18.5<br>
Nageoire nu 2.6<br>
Camouflages phi 0.2<br>
Comportement Prevoyante<br>
<br>
Type Rusé p: 0.25<br>
Yeux delta 48.6 alpha 0.78 gamma 0.4<br>
Comportement Multiple<br>
<br>
Type Chasseur p: 0.25<br>
Yeux delta 31. alpha 0.66 gamma 0.4<br>
Oreilles delta 16.9 gamma 0.88<br>
Nageoire nu 1.8<br>
Comportement Kamikaze<br>
<br>
Stop<br>
</code>
