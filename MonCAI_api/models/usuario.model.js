'use strict';

module.exports = (sequelize, DataTypes) => {
  const Usuario = sequelize.define('usuario', {
    idUsuario: {
      type: DataTypes.BIGINT,
      primaryKey: true,
      autoIncrement: true
    },
    nombre: DataTypes.STRING,
    email: {
      type: DataTypes.STRING,
      unique: true
    },
    password: DataTypes.STRING
  }, {
    sequelize
  });

  return Usuario;
};
