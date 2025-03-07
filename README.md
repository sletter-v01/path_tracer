# Path Tracer Project

## Description

Ce projet implémente un rendu par tracé de chemins (path tracing) simple et efficace en C++. Il démontre les principes fondamentaux du ray tracing, y compris la gestion de différents matériaux tels que Lambertian, Metal et Dielectric. Ce projet est idéal pour les étudiants et les passionnés de graphisme informatique et de techniques de rendu.

## Fonctionnalités

- **Tracé de chemins :** Simule les interactions complexes de la lumière avec les surfaces pour produire des images réalistes.
- **Matériaux divers :** Inclut des matériaux diffus (Lambertian), métalliques et diélectriques (verre) pour des effets de réflexion et de réfraction variés.
- **Multithreading :** Exploite le parallélisme pour accélérer le rendu sur les systèmes multi-cœurs.
- **Scène aléatoire :** Génère des scènes aléatoires avec des sphères de différents matériaux pour tester les capacités du moteur de rendu.
- **Utilisation des méthodes de Monte Carlo :** Utilise des techniques de Monte Carlo pour l'échantillonnage aléatoire des directions de rayons, améliorant ainsi la qualité et la précision du rendu.

## Technologies

- **Langage :** C++
- **Graphisme :** Tracé de chemins, Ray Tracing
- **Outils :** Utilisation des bibliothèques standard C++ et de fonctions personnalisées pour la génération aléatoire, les vecteurs mathématiques et les rayons.

## Public cible

Ce projet est conçu pour :
- Les étudiants en informatique et en graphisme souhaitant apprendre les bases du ray tracing.
- Les développeurs passionnés par les techniques de rendu réaliste.
- Toute personne intéressée par la création de moteurs de rendu en C++.

## Instructions d'installation

1. Clonez le repository :
    ```sh
    git clone https://github.com/sletter-v01/PathTracer.git
    cd PathTracer
    ```

2. Créez un répertoire de construction et compilez le projet :
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

3. Exécutez le programme :
    ```sh
    ./path_tracer
    ```

## Utilisation

Le programme génère une image en utilisant le rendu par tracé de chemins et l'enregistre sous le nom `output.ppm`. Vous pouvez ajuster les paramètres de rendu dans le fichier `main.cpp` pour modifier la qualité de l'image et les performances.

## Détails techniques

### Matériaux
- **Lambertian :** Matériau diffus qui diffuse la lumière uniformément dans toutes les directions.
- **Metal :** Matériau métallique qui réfléchit la lumière de manière spéculaire avec un certain flou.
- **Dielectric :** Matériau transparent (comme le verre) qui peut réfracter ou réfléchir la lumière en fonction de l'angle d'incidence et de l'indice de réfraction.

### Méthodes de Monte Carlo
- Utilisées pour l'échantillonnage aléatoire des directions de diffusion et de réflexion.
- Permettent de simuler des interactions de lumière complexes et de produire des images réalistes avec des effets de lumière douce et des ombres.

### Multithreading
- Le rendu est accéléré en utilisant le parallélisme, répartissant les calculs sur plusieurs cœurs de processeur.
- Chaque thread rend une section de l'image, puis les résultats sont combinés pour produire l'image finale.

## Contribution

Les contributions sont les bienvenues ! Veuillez soumettre des pull requests ou ouvrir des issues pour discuter des modifications proposées.
