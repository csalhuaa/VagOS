# Configuración de WSL (Windows Subsystem for Linux)

## Configuración en Windows

En el buscador de Windows, buscar "**Activar y desactivar características de Windows**". Activar las siguientes opciones:

* **Plataforma de máquina virtual**
* **Subsistema de Linux para Windows**

## Instalación en Terminal

### Listar distribuciones Linux disponibles
```bash
wsl --install
```

### Instalar una distribución específica
```bash
wsl --install -d <nombre-de-distro>
```

## Acceso a la Distribución

Una vez instalada la distribución, ingresar en terminal:
```bash
wsl
```

## Instalación de Dependencias

### Actualizar repositorios
```bash
sudo apt update
```

### Instalar herramientas de desarrollo
```bash
sudo apt install git make build-essential nasm parted dosfstools tree qemu-system gdb mtools xorriso
```

## Makefile targets

To create required files (only do this once):
    
    make setup

To compile (and run) just run:

    make

You can cleanup garbage with the classic:

    make clean

## Acknoledgements and credits

- Keep-Konect [github](https://github.com/Keep-Konect)
- Marco Paland (info@paland.com)
- Lukás Chmela
- Absurd Poncho
- The Limine project
- strawberryhacker