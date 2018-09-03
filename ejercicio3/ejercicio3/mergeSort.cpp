void AlgoritmosIndexada::mergeSort(lista& l, int inicio, int final) {
	if (inicio < final) {
		int cantElem = 0;
		int min = inicio;
		int max = final;
		while (min <= max) {
			cantElem++;
			min++;
		}
		cantElem = cantElem / 2;
		int mitad = (inicio - 1) + cantElem;
		mergeSort(l, inicio, mitad);
		mergeSort(l, mitad + 1, final);

		merge(l, inicio, mitad, final);
	}
}

void AlgoritmosIndexada::merge(lista& l, int inicio, int medio, int final) {
	lista l2;
	l2.iniciar();
	int insertar = 1;
	for (int i = inicio; i <= final; i++) {
		l2.insertar(l.recuperar(i), insertar);
		insertar++;
	}

	int i = 1;
	int j = (medio%l2.numElem()) + 1;
	int mitad = medio % l2.numElem();
	int max = l2.numElem();
	int k = inicio;

	while (i <= mitad && j <= max) {
		if (l2.recuperar(i) <= l2.recuperar(j)) {
			l.modificarElem(l2.recuperar(i), k);
			i++;
		}
		else {
			l.modificarElem(l2.recuperar(j), k);
			j++;
		}
		k++;
	}
	while (i <= mitad) {
		l.modificarElem(l2.recuperar(i), k);
		i++;
		k++;
	}
	while (j <= max) {
		l.modificarElem(l2.recuperar(j), k);
		j++;
		k++;
	}
}