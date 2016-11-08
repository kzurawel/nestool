#include "edittiledialog.h"
#include "ui_edittiledialog.h"

EditTileDialog::EditTileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTileDialog)
{
    ui->setupUi(this);

    ui->tileWidget->setFixedSize(QSize(160, 160));
    ui->tileWidget->setEditable(true);
    ui->swatch0->setSelected(true);
    connect(ui->swatch0, SIGNAL(clicked()), this, SLOT(paletteClicked()));
    connect(ui->swatch1, SIGNAL(clicked()), this, SLOT(paletteClicked()));
    connect(ui->swatch2, SIGNAL(clicked()), this, SLOT(paletteClicked()));
    connect(ui->swatch3, SIGNAL(clicked()), this, SLOT(paletteClicked()));
    mCurrentColor = 0;
}

EditTileDialog::~EditTileDialog()
{
    delete ui;
}

void EditTileDialog::setData(char *data)
{
    ui->tileWidget->setData(data);
}

char *EditTileDialog::chrData()
{
    return ui->tileWidget->chrData();
}

void EditTileDialog::setPalette(QList<QColor> colors)
{
    ui->tileWidget->setPalette(colors);
    ui->swatch0->setColor(colors.at(0));
    ui->swatch1->setColor(colors.at(1));
    ui->swatch2->setColor(colors.at(2));
    ui->swatch3->setColor(colors.at(3));
}

void EditTileDialog::paletteClicked()
{
    Swatch *from = qobject_cast<Swatch*>(sender());
    QColor color = from->getColor();
    for (int i = 0; i < 4; ++i) {
        Swatch *swatch = this->findChild<Swatch *>(QString("swatch%1").arg(i));
        if (swatch) {
            if (swatch == from) {
                mCurrentColor = i;
                from->setSelected(true);
            } else
                swatch->setSelected(false);
        }
    }
    ui->tileWidget->setCurrentColor(mCurrentColor);
}

